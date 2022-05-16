/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttorbeyn <ttorbeyn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:09:15 by ttorbeyn          #+#    #+#             */
/*   Updated: 2022/05/16 16:09:16 by ttorbeyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	check_dead(t_data *data)
{
	int			i;

	while (!data->philo_sated)
	{
		i = -1;
		while (++i < data->nb_of_philo && !data->dead)
		{
			if (get_time(data, i) > data->t_to_die)
				hes_dead(data, i);
		}
		if (data->dead)
			break ;
		i = 0;
		ft_mutex_lock(&data->eat, LOCK, "eat");
		while (data->nb_of_t_each_philo_must_eat != -1 && i < data->nb_of_philo
			&& data->philo[i].nb_of_eat >= data->nb_of_t_each_philo_must_eat)
			i++;
		if (i == data->nb_of_philo)
			data->philo_sated = 1;
		ft_mutex_lock(&data->eat, UNLOCK, "eat");
	}
	return (0);
}

int	philo_eat(t_data *data, t_philo *philo)
{
	ft_mutex_lock(&data->fork[philo->right_fork], LOCK, "right fork");
	print_status(data, philo, "has taken [his right] a fork");
	ft_mutex_lock(&data->fork[philo->left_fork], LOCK, "left fork");
	print_status(data, philo, "has taken [his left] a fork");
	print_status(data, philo, "is eating");
	ft_mutex_lock(&data->eat, LOCK, "last time eat");
	philo->last_time_eat = get_timestamp();
	ft_mutex_lock(&data->eat, UNLOCK, "last time eat");
	philo_sleep(data->t_to_eat, data);
	ft_mutex_lock(&data->eat, LOCK, "number of eat");
	philo->nb_of_eat++;
	ft_mutex_lock(&data->eat, UNLOCK, "number of eat");
	ft_mutex_lock(&data->fork[philo->right_fork], UNLOCK, "right fork");
	ft_mutex_lock(&data->fork[philo->left_fork], UNLOCK, "left fork");
	return (0);
}

void	*function(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		sated;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2)
		usleep(15000);
	while (!data->dead)
	{
		philo_eat(data, philo);
		ft_mutex_lock(&data->eat, LOCK, "philo sated");
		sated = data->philo_sated;
		ft_mutex_lock(&data->eat, UNLOCK, "philo sated");
		if (sated)
			break ;
		print_status(data, philo, "is sleeping");
		philo_sleep(data->t_to_sleep, data);
		print_status(data, philo, "is thinking");
	}
	return (NULL);
}

int	philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		data->philo[i].last_time_eat = get_timestamp();
		pthread_create(&data->philo[i].philo_thread, NULL,
			function, &data->philo[i]);
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
	destroy_mutex(&data);
	ft_free_all(&data);
	return (0);
}
