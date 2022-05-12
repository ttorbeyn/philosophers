#include "includes/philo.h"

long long	get_timestamp(void)
{
	struct timeval	new;

	gettimeofday(&new, NULL);
	return ((new.tv_sec * 1000) + (new.tv_usec / 1000));
}

int		print_status(t_data *data, t_philo *philo, char *status)
{
	if (pthread_mutex_lock(&data->write))
		ft_error("Lock write");
	if(!(data->dead))
	{
		ft_putnbr(get_timestamp() - data->timestamp_start);
		ft_putstr("\t");
		ft_putnbr(philo->id + 1);
		ft_putstr(" ");
		ft_putstr(status);
		ft_putstr("\n");
	}
	if (pthread_mutex_unlock(&data->write))
		ft_error("Lock write");
	return (0);
}

long long 	time_diff(long long old, long long new)
{
	return(new - old);
}

int		philo_sleep(long long t_to_sleep, t_data *data)
{
	long long	i;

	i = get_timestamp();
	while (!(data->dead))
	{
		if (time_diff(i, get_timestamp()) >= t_to_sleep)
			break ;
		usleep(50);
	}
	return (0);
}