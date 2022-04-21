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
# include <time.h>
# include <sys/time.h>

# define EATING 0
# define SLEEPING 1
# define THINKING 2

typedef struct s_philo
{
	int	id;
	int fork_id;
	int	state;
}				t_philo;

typedef struct s_data
{
	int		nb_of_philo;
	int		t_to_die;
	int		t_to_eat;
	int 	t_to_sleep;
	int		nb_of_t_each_philo_must_eat;
	t_philo	*philo;
}				t_data;



//ft_error.c
int	ft_exit(char *error);

//ft_atoi.c
int	ft_atoi(const char *str);

#endif
