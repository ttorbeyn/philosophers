#include "includes/philo.h"

int		ft_write(t_data *data, t_philo *philo, char *status)
{
	pthread_mutex_lock(&data->write);
	printf("%lld\t | ", get_timestamp() - data->timestamp_start);
	printf("philo %d\t", philo->id);
	printf("%s\n", status);
//	printf("start : %lld\n", data->timestamp_start);
//	printf("current : %lld\n", get_timestamp());
	pthread_mutex_unlock(&data->write);
	return (0);
}

int		eat(t_data *data, t_philo *philo)
{
	int error;

	if (philo->id % 2)
		usleep(15000);
	if (pthread_mutex_lock(&data->fork[philo->right_fork]))
	{
		printf("Lock error right fork\n");
		return (1);
	}
	if (ft_write(data, philo, "has taken his right fork"))
	{
		printf("Write error right fork\n");
		return (1);
	}
	if (pthread_mutex_lock(&data->fork[philo->left_fork]))
	{
		printf("Lock error left fork\n");
		return (1);
	}
	if (ft_write(data, philo, "has taken his left fork"))
	{
		printf("Write error left fork\n");
		return (1);
	}
	if (ft_write(data, philo, "has eaten"))
	{
		printf("Write error eaten\n");
		return (1);
	}
	pthread_mutex_unlock(&data->fork[philo->left_fork]);
	pthread_mutex_unlock(&data->fork[philo->right_fork]);
	philo->last_time_eat = get_timestamp();
	ft_write(data, philo, "is sleeping");
	usleep(data->t_to_eat);
	return (0);
}

int init_mutex(t_data *data)
{
	int i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->fork)
		ft_exit("Malloc error");
	while (i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			ft_exit("Mutex error");
		i++;
	}
	if (pthread_mutex_init(&data->write, NULL))
		ft_exit("Mutex error");
	return (0);
}

int		check_dead(t_data *data)
{
	int	i;
	long long time;

	i = 0;
	while (i < data->nb_of_philo)
	{
		time = data->philo->last_time_eat - get_timestamp();
		if (time > data->t_to_die)
		{
			ft_write(data, &data->philo[i], "has died\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void*	function(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	init_mutex(data);
	while (!check_dead(data))
		eat(data, philo);
	usleep(100);
	return (0);
}


int philo(t_data *data)
{
	int 		i;
//	t_philo		*philo;
//
//	philo = data->philo;
	i = 0;
//	data->philo->philo_thread = malloc(sizeof(pthread_t) * data->nb_of_philo);
//	if (!data->philo->philo_thread)
//		ft_exit("Malloc error");
	data->t_to_die = 5;
	data->timestamp_start = get_timestamp();
//	data->timestamp_start = start.tv_sec * 1000 + start.tv_usec / 1000;
//	printf("start1 : %lld\n", data->timestamp_start);
	while (i < data->nb_of_philo)
	{
		pthread_create(&data->philo[i].philo_thread, NULL, function, &data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_join(data->philo[i].philo_thread, NULL);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		ft_exit("Not the right number of arguments");
	data_set(&data, ac, av);
	philo_set(&data);
	philo(&data);
	return (0);
}