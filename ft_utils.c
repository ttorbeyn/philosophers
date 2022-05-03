#include "includes/philo.h"

long long	get_timestamp(void)
{
	struct timeval	new;

	gettimeofday(&new, NULL);
	return (new.tv_sec * 1000 + new.tv_usec / 1000);
}
