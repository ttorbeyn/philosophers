#include "includes/philo.h"

void*	function(void *arg)
{
//	printf("thread 1\n");
	if (!arg)
		return (0);
	return (0);
}

int philo_set(t_data *data)
{
	int	i;
	int x;

	x = 0;
	i = 1;
	while (i < data->nb_of_philo)
		data->philo[x++].id = i++;
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
	return (0);
}

long get_duration_process()
{
	struct timeval	old;
	struct timeval	new;
	long time;

	gettimeofday(&old, NULL);
//	printf("%ld\n", (time_base.tv_sec * 1000000 + time_base.tv_usec));
	usleep(50);
	gettimeofday(&new, NULL);
//	printf("%ld\n", (time_new.tv_sec * 1000000 + time_new.tv_usec));
	time = (new.tv_sec * 1000000 + new.tv_usec) - (old.tv_sec * 1000000 + old.tv_usec);
//	printf("%ld\n", time);
	return (time);
}

int philo(t_data *data)
{
	int i;

	i = data->nb_of_philo;
	pthread_t	philo1;
	pthread_create(&philo1, NULL, function, NULL);
	pthread_join(philo1, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		ft_exit("Not the right number of arguments");
	get_duration_process();
	data_set(&data, ac, av);
	philo(&data);
	return (0);
}