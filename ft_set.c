#include "includes/philo.h"

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
	data->timestamp_start = get_timestamp();
	if (data->nb_of_philo < 2)
		return (1);
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