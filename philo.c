#include "includes/philo.h"

int	data_set(t_data *data, int ac, char **av)
{


	data->nb_of_philo = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep= ft_atoi(av[4]);
	if (ac == 6)
		data->nb_of_t_each_philo_must_eat= ft_atoi(av[5]);
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philo)
		ft_exit("Malloc error");


	return (0);
}

int philo_set(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		data->philo[i].id = i;
		data->philo[i].right_fork = i;
		data->philo[i].left_fork = (i + 1) % data->nb_of_philo;
		data->philo[i].last_time_eat = data->timestamp_start;
		data->philo[i].data = data;
		i++;
	}
	return (0);
}

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

void*	function(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2)
		usleep(15000);
	pthread_mutex_lock(&data->fork[philo->right_fork]);
	ft_write(data, philo, "has taken his right fork");
	pthread_mutex_lock(&data->fork[philo->left_fork]);
	ft_write(data, philo, "has taken his left fork");
	ft_write(data, philo, "has eaten");
	usleep(data->t_to_eat);
	pthread_mutex_unlock(&data->fork[philo->left_fork]);
	pthread_mutex_unlock(&data->fork[philo->right_fork]);
	//	printf("%d\n", data->t_to_eat);

	ft_write(data, philo, "is sleeping");
//	printf("coucou\n");
	return (0);
}

long long	get_timestamp(void)
{
	struct timeval	new;
//	long time;

	gettimeofday(&new, NULL);
//	printf("start2 : %f\n", data->timestamp_start);

//	time = () - data->timestamp_start;
//	printf("time  : %ld\n", time);
	return (new.tv_sec * 1000 + new.tv_usec / 1000);
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
	data->timestamp_start = get_timestamp();
	data->t_to_die = 5;
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
