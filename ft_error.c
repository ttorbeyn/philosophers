#include "./includes/philo.h"

int	ft_exit(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

int ft_error(char *error)
{
	write(1, "Error: ", 7);
	write(1, error, ft_strlen(error));
	write(1, "\n", 1);
	return (1);
}