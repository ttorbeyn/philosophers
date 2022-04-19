#include "includes/philo.h"

void*	function(void *arg)
{
	printf("thread 1\n");
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
	while (i < data->number_of_philosophers)
		data->philo[x++].id = i++;
	return (0);
}

int	data_set(t_data *data, int ac, char **av)
{
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep= ft_atoi(av[4]);
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat= ft_atoi(av[5]);
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philo)
		ft_exit("Malloc error");
	return (0);
}

int	main(int ac, char **av)
{
	int state;
	t_data	data;

	state = EATING;


	if (ac != 5 && ac != 6)
		ft_exit("Not the right number of arguments");
	data_set(&data, ac, av);


	pthread_t	philo1;
	pthread_create(&philo1, NULL, function, NULL);
	pthread_join(philo1, NULL);
	printf("nbr philo : %d\n", data.number_of_philosophers);
	printf("time die: %d\n", data.time_to_die);
	printf("time eat : %d\n", data.time_to_eat);
	printf("time sleep : %d\n", data.time_to_sleep);
	return (0);
}