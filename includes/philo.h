#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <string.h>
# include <sys/wait.h>

# include <pthread.h>

# define EATING 0
# define SLEEPING 1
# define THINKING 2

typedef struct s_philo
{
	int	id;
}				t_philo;

typedef struct s_data
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int 	time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
	t_philo	*philo;
}				t_data;

//ft_error.c
int	ft_exit(char *error);

//ft_atoi.c
int	ft_atoi(const char *str);

#endif
