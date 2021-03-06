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

#include "../includes/philo.h"

int	check_dead(t_data *data)
{
	int			i;

	while (!data->dead_sated)
	{
		i = 0;
		while (i < data->nb_of_philo && !data->dead_sated)
		{
			if (get_time(data, i) > data->t_to_die)
				hes_dead(data, i);
			i++;
		}
		if (data->dead_sated)
			break ;
		i = 0;
		ft_mutex_lock(&data->eat, LOCK, "eat");
		while (data->nb_of_t_each_philo_must_eat != -1 && i < data->nb_of_philo
			&& data->philo[i].nb_of_eat >= data->nb_of_t_each_philo_must_eat)
			i++;
		ft_mutex_lock(&data->eat, UNLOCK, "eat");
		ft_mutex_lock(&data->died, LOCK, "died");
		if (i == data->nb_of_philo)
			data->dead_sated = 1;
		ft_mutex_lock(&data->died, UNLOCK, "died");
	}
	return (0);
}

int	philo_eat(t_data *data, t_philo *philo)
{
	ft_mutex_lock(&data->fork[philo->right_fork], LOCK, "right fork");
	print_status(data, philo, "has taken a fork");
	ft_mutex_lock(&data->fork[philo->left_fork], LOCK, "left fork");
	print_status(data, philo, "has taken a fork");
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
	int		dead_sated;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2)
		usleep(15000);
	dead_sated = 0;
	while (!dead_sated)
	{
		philo_eat(data, philo);
		ft_mutex_lock(&data->died, LOCK, "philo sated");
		dead_sated = data->dead_sated;
		ft_mutex_lock(&data->died, UNLOCK, "philo sated");
		if (dead_sated)
			break ;
		print_status(data, philo, "is sleeping");
		philo_sleep(data->t_to_sleep, data);
		print_status(data, philo, "is thinking");
		ft_mutex_lock(&data->died, LOCK, "died");
		dead_sated = data->dead_sated;
		ft_mutex_lock(&data->died, UNLOCK, "died");
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
	int		ret;

	if (ac != 5 && ac != 6)
		return (ft_error("Not the right number of arguments"));
	ret = data_set(&data, ac, av);
	if (ret == 1)
		ft_error("Data set");
	if (ret)
		return (1);
	philo_set(&data);
	if (init_mutex(&data))
		return (1);
	philo(&data);
	if (destroy_mutex(&data))
		return (1);
	ft_free_all(&data);
	return (0);
}
