#include "includes/philo.h"

void*	function(void *arg)
{
	printf("thread 1\n");

	if (!arg)
		return (0);
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
	}
	return (0);
}




int	data_set(t_data *data, int ac, char **av)
{
	struct timeval	start;

	data->nb_of_philo = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep= ft_atoi(av[4]);
	if (ac == 6)
		data->nb_of_t_each_philo_must_eat= ft_atoi(av[5]);
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philo)
		ft_exit("Malloc error");
	gettimeofday(&start, NULL);
	data->timestamp_start = start.tv_sec * 1000000 + start.tv_usec;
	return (0);
}

long get_timestamp(t_data *data)
{
	struct timeval	new;
	long time;

//	printf("%ld\n", (time_base.tv_sec * 1000000 + time_base.tv_usec));
	gettimeofday(&new, NULL);
//	printf("%ld\n", (time_new.tv_sec * 1000000 + time_new.tv_usec));
	time = (new.tv_sec * 1000000 + new.tv_usec) - data->timestamp_start;
//	printf("%ld\n", time);
	return (time);
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
	int i;

	i = 0;
	data->philo_thread = malloc(sizeof(pthread_t) * data->nb_of_philo);
	if (!data->philo_thread)
		ft_exit("Malloc error");


	while (i < data->nb_of_philo)
	{
		pthread_create(&data->philo_thread[i], NULL, function, NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_join(data->philo_thread[i], NULL);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		ft_exit("Not the right number of arguments");
	get_timestamp(&data);
	data_set(&data, ac, av);
	philo(&data);
	return (0);
}