/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttorbeyn <ttorbeyn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:09:29 by ttorbeyn          #+#    #+#             */
/*   Updated: 2022/05/16 16:09:30 by ttorbeyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_timestamp(void)
{
	struct timeval	new;

	gettimeofday(&new, NULL);
	return ((new.tv_sec * 1000) + (new.tv_usec / 1000));
}

int	print_status(t_data *data, t_philo *philo, char *status)
{
	int	dead;

	ft_mutex_lock(&data->died, LOCK, "dead");
	dead = data->dead;
	ft_mutex_lock(&data->died, UNLOCK, "dead");
	ft_mutex_lock(&data->write, LOCK, "write");
	if (!dead)
	{
		ft_putnbr(get_timestamp() - data->timestamp_start);
		ft_putstr("\t");
		ft_putnbr(philo->id + 1);
		ft_putstr(" ");
		ft_putstr(status);
		ft_putstr("\n");
	}
	ft_mutex_lock(&data->write, UNLOCK, "write");
	return (0);
}

long long	time_diff(long long old, long long new)
{
	return (new - old);
}

int	philo_sleep(long long t_to_sleep, t_data *data)
{
	long long	i;
	int			dead;

	i = get_timestamp();
	ft_mutex_lock(&data->died, LOCK, "dead");
	dead = data->dead;
	ft_mutex_lock(&data->died, UNLOCK, "dead");
	while (!dead)
	{
		if (time_diff(i, get_timestamp()) >= t_to_sleep)
			break ;
		usleep(50);
	}
	return (0);
}

int	ft_mutex_lock(pthread_mutex_t *var, int lock, char *str)
{
	if (lock == LOCK)
	{
		if (pthread_mutex_lock(var))
			ft_error(ft_strjoin("Mutex lock", str));
	}
	if (lock == UNLOCK)
	{
		if (pthread_mutex_unlock(var))
			ft_error(ft_strjoin("Mutex unlock", str));
	}
	return (0);
}
