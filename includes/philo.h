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
	int				id;
	int 			right_fork;
	int 			left_fork;
	long long		last_time_eat;
	int				state;
	pthread_t		philo_thread;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				nb_of_philo;
	int				t_to_die;
	int				t_to_eat;
	int 			t_to_sleep;
	int				nb_of_t_each_philo_must_eat;
	long long		timestamp_start;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
}				t_data;


//ft_philo.c
long long	get_timestamp();

//ft_set.c
int	data_set(t_data *data, int ac, char **av);
int philo_set(t_data *data);

//ft_utils.c
long long	get_timestamp(void);

//ft_error.c
int	ft_exit(char *error);

//ft_atoi.c
int	ft_atoi(const char *str);

#endif
