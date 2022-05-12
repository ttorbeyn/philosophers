#include "includes/philo.h"

int		check_dead(t_data *data)
{
	int	i;

	i = 0;
	while (!data->philo_sated)
	{
		while (i < data->nb_of_philo && !data->dead)
		{
			if (time_diff(data->philo[i].last_time_eat, get_timestamp()) > data->t_to_die)
			{
				print_status(data, &data->philo[i], "died\n");
				data->dead = 1;
			}
			i++;
		}
		if (data->dead)
			break ;
		i = 0;
		while (data->nb_of_t_each_philo_must_eat != -1 && i < data->nb_of_philo
			&& data->philo[i].nb_of_eat >= data->nb_of_t_each_philo_must_eat)
			i++;
		if (i == data->nb_of_philo)
			data->philo_sated = 1;
	}
	return (0);
}

int		philo_eat(t_data *data, t_philo *philo)
{
	if (pthread_mutex_lock(&data->fork[philo->right_fork]))
		ft_error("Lock right fork");
	print_status(data, philo, "has taken [his right] a fork");
	if (pthread_mutex_lock(&data->fork[philo->left_fork]))
		ft_error("Lock left fork");
	print_status(data, philo, "has taken [his left] a fork");
	print_status(data, philo, "is eating");
	philo->last_time_eat = get_timestamp();
	philo_sleep(data->t_to_eat, data);
	philo->nb_of_eat++;
	pthread_mutex_unlock(&data->fork[philo->left_fork]);
	pthread_mutex_unlock(&data->fork[philo->right_fork]);
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
	while (!data->dead)
	{
		philo_eat(data, philo);
		if (data->philo_sated)
			break ;
		print_status(data, philo, "is sleeping");
		philo_sleep(data->t_to_sleep, data);
		print_status(data, philo, "is thinking");
	}
	return (NULL);
}

int philo(t_data *data)
{
	int 		i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_create(&data->philo[i].philo_thread, NULL, function, &data->philo[i]);
		data->philo[i].last_time_eat = get_timestamp();
		i++;
	}
	check_dead(data);
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
		ft_error("Not the right number of arguments");
	if (data_set(&data, ac, av))
		ft_error("Data set");
	philo_set(&data);
	init_mutex(&data);
	philo(&data);
	return (0);
}
