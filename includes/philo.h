/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttorbeyn <ttorbeyn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:11:11 by ttorbeyn          #+#    #+#             */
/*   Updated: 2022/05/16 17:11:13 by ttorbeyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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

# define LOCK 1
# define UNLOCK 2

typedef struct s_philo
{
	int				id;
	int				right_fork;
	int				left_fork;
	long long		last_time_eat;
	int				nb_of_eat;
	struct s_data	*data;
	pthread_t		philo_thread;
}				t_philo;

typedef struct s_data
{
	int				nb_of_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				dead_sated;
	int				nb_of_t_each_philo_must_eat;
	long long		timestamp_start;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
	pthread_mutex_t	eat;
	pthread_mutex_t	died;
}				t_data;

//ft_philo.c

//ft_set.c
int			init_mutex(t_data *data);
int			data_set(t_data *data, int ac, char **av);
int			philo_set(t_data *data);
int			destroy_mutex(t_data *data);

//ft_utils.c
long long	get_timestamp(void);
int			print_status(t_data *data, t_philo *philo, char *status);
long long	time_diff(long long old, long long new);
int			philo_sleep(long long t_to_sleep, t_data *data);
int			ft_mutex_lock(pthread_mutex_t *var, int lock, char *str);

//ft_utils2
int			only_one_dead(t_data *data);
int			hes_dead(t_data *data, int i);
long long	get_time(t_data *data, int i);

//ft_error.c
int			ft_error(char *error);
int			ft_free_all(t_data *data);

//libft
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
void		ft_putnbr(long long n);
void		ft_putstr(char *s);
void		ft_putchar(char c);
char		*ft_strjoin(char const *s1, char const *s2);

#endif
