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
		printf("%lld\t | ", get_timestamp() - data->timestamp_start);
		printf("philo %d\t", philo->id + 1);
		printf("%s\n", status);
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