/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttorbeyn <ttorbeyn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:28:38 by ttorbeyn          #+#    #+#             */
/*   Updated: 2022/05/16 17:28:39 by ttorbeyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	only_one_dead(t_data *data)
{
	usleep(data->t_to_die);
	ft_putnbr(data->t_to_die);
	write(1, "\t1 died\n", 8);
	return (2);
}

int	hes_dead(t_data *data, int i)
{
	print_status(data, &data->philo[i], "died");
	ft_mutex_lock(&data->died, LOCK, "died");
	data->dead_sated = 1;
	ft_mutex_lock(&data->died, UNLOCK, "died");
	return (0);
}

long long	get_time(t_data *data, int i)
{
	long long	time;

	ft_mutex_lock(&data->eat, LOCK, "eat");
	time = time_diff(data->philo[i].last_time_eat, get_timestamp());
	ft_mutex_lock(&data->eat, UNLOCK, "eat");
	return (time);
}
