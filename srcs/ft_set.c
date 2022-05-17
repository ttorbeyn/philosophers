/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttorbeyn <ttorbeyn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:09:22 by ttorbeyn          #+#    #+#             */
/*   Updated: 2022/05/16 16:09:23 by ttorbeyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->fork)
		return (ft_error("Malloc error"));
	while (i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (ft_error("Mutex error"));
		i++;
	}
	if (pthread_mutex_init(&data->write, NULL))
		return (ft_error("Mutex error"));
	if (pthread_mutex_init(&data->eat, NULL))
		return (ft_error("Mutex error"));
	if (pthread_mutex_init(&data->died, NULL))
		return (ft_error("Mutex error"));
	return (0);
}

int	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (pthread_mutex_destroy(&data->fork[i]))
			return (ft_error("Mutex error"));
		i++;
	}
	if (pthread_mutex_destroy(&data->write))
		return (ft_error("Mutex error"));
	if (pthread_mutex_destroy(&data->eat))
		return (ft_error("Mutex error"));
	if (pthread_mutex_destroy(&data->died))
		return (ft_error("Mutex error"));
	return (0);
}

int	philo_set(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		data->philo[i].id = i;
		data->philo[i].right_fork = i;
		data->philo[i].left_fork = (i + 1) % data->nb_of_philo;
		data->philo[i].last_time_eat = 0;
		data->philo[i].nb_of_eat = 0;
		data->philo[i].data = data;
		i++;
	}
	return (0);
}

int	data_set(t_data *data, int ac, char **av)
{
	data->nb_of_philo = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	data->philo_sated = 0;
	if (data->nb_of_philo < 2)
		return (write(1, "0\t1 died\n", 9) + 2);
	if (data->nb_of_philo < 1 || data->t_to_die < 0 || data->t_to_eat < 0
		|| data->t_to_sleep < 0)
		return (1);
	data->dead = 0;
	if (ac == 6)
	{
		data->nb_of_t_each_philo_must_eat = ft_atoi(av[5]);
		if (data->nb_of_t_each_philo_must_eat <= 0)
			return (1);
	}
	else
		data->nb_of_t_each_philo_must_eat = -1;
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philo)
		return (ft_error("Malloc error"));
	data->timestamp_start = get_timestamp();
	return (0);
}
