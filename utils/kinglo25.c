#include "philo.h"

int	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	ft_sleep(int time, t_glob *g)
{
	long long	t;

	t = timestamp();
	(void)g;
	while (time_diff(t, timestamp()) <= time)
		usleep(50);
}

int	error(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (42);
}

int	mutex_destroy(t_glob *g)
{
	int	i;

	i = 0;
	while (i < g->nb_phil)
	{
		if (pthread_mutex_destroy(&g->forks[i]))
			return (42);
		i++;
	}
	if (pthread_mutex_destroy(&g->check))
		return (42);
	if (pthread_mutex_destroy(&g->writing))
		return (42);
	return (0);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	print_status(char *str, int id, t_glob *g)
{
	pthread_mutex_lock(&g->writing);
	if (!g->died)
	{
		printf("%lli ", timestamp() - g->first_timestamp);
		printf("%i ", id + 1);
		printf("%s", str);
	}
	pthread_mutex_unlock(&g->writing);
	return (0);
}

static int	init_mutex(t_glob *g)
{
	int	i;

	i = 0;
	while (i < g->nb_phil)
	{
		if (pthread_mutex_init(g->forks + i, NULL))
			return (42);
		i++;
	}
	if (pthread_mutex_init(&g->check, NULL))
		return (42);
	if (pthread_mutex_init(&g->writing, NULL))
		return (42);
	return (0);
}

static void	init_philosophers(t_glob *g)
{
	int	i;

	i = 0;
	while (i < g->nb_phil)
	{
		g->phil[i].id = i;
		g->phil[i].nb_ate = 0;
		g->phil[i].l_fork = i;
		g->phil[i].r_fork = (i + 1) % g->nb_phil;
		g->phil[i].t_last_meal = 0;
		g->phil[i].g = g;
		i++;
	}
}

int	init_all(char **av, t_glob *g)
{
	g->nb_phil = ft_atoi(av[1]);
	g->t_die = ft_atoi(av[2]);
	g->t_eat = ft_atoi(av[3]);
	g->t_sleep = ft_atoi(av[4]);
	g->ate_max = 0;
	g->died = 0;
	if (init_mutex(g))
		return (42);
	if (g->nb_phil < 1 || g->nb_phil > 200 || g->t_die < 60
		|| g->t_eat < 60 || g->t_sleep < 60)
		return (42);
	if (av[5])
	{
		g->nb_max_eat = ft_atoi(av[5]);
		if (g->nb_max_eat <= 0)
			return (42);
	}
	else
		g->nb_max_eat = -1;
	init_philosophers(g);
	return (0);
}

static int	philo_eats(t_phil *phil, t_glob *g)
{
	if (pthread_mutex_lock(&g->forks[phil->l_fork]))
		return (42);
	if (print_status("has taken a fork\n", phil->id, g))
		return (42);
	if (phil->l_fork == phil->r_fork)
		return (pthread_mutex_unlock(&g->forks[phil->l_fork]));
	if (pthread_mutex_lock(&g->forks[phil->r_fork]))
		return (42);
	if (print_status("has taken a fork\n", phil->id, g))
		return (42);
	if (pthread_mutex_lock(&g->check))
		return (42);
	phil->t_last_meal = timestamp();
	if (print_status("is eating\n", phil->id, g))
		return (42);
	if (pthread_mutex_unlock(&g->check))
		return (42);
	ft_sleep(g->t_eat, g);
	phil->nb_ate++;
	if (pthread_mutex_unlock(&g->forks[phil->l_fork]))
		return (42);
	if (pthread_mutex_unlock(&g->forks[phil->r_fork]))
		return (42);
	usleep(100);
	return (0);
}

static void	*routine(void *arg)
{
	t_phil	*phil;
	t_glob	*g;

	phil = (t_phil *)arg;
	g = phil->g;
	if (phil->id % 2)
		usleep(15000);
	while (!g->died && !g->ate_max)
	{
		philo_eats(phil, g);
		if (phil->l_fork == phil->r_fork)
			break ;
		print_status("is sleeping\n", phil->id, g);
		ft_sleep(g->t_sleep, g);
		print_status("is thinking\n", phil->id, g);
		usleep(500);
	}
	return (NULL);
}

static int	check_if_dead(t_glob *g, t_phil *p, int i)
{
	while (!g->ate_max)
	{
		i = 0;
		while (i < g->nb_phil && !(g->died))
		{
			pthread_mutex_lock(&g->check);
			if (time_diff(p[i].t_last_meal, timestamp()) >= g->t_die)
			{
				if (print_status("died\n", i, g))
					return (42);
				g->died = 1;
			}
			pthread_mutex_unlock(&g->check);
			i++;
		}
		if (g->died)
			break ;
		i = 0;
		while (g->nb_max_eat != -1 && i < g->nb_phil
			   && p[i].nb_ate >= g->nb_max_eat)
			i++;
		if (i == g->nb_phil)
			g->ate_max = 1;
	}
	return (0);
}

int	philo(t_glob *g)
{
	int		i;
	t_phil	*phil;

	i = 0;
	phil = g->phil;
	g->first_timestamp = timestamp();
	while (i < g->nb_phil)
	{
		if (pthread_create(&phil[i].thread_id, NULL, routine, phil + i))
			return (42);
		pthread_mutex_lock(&g->check);
		phil[i].t_last_meal = timestamp();
		pthread_mutex_unlock(&g->check);
		usleep(500);
		i++;
	}
	check_if_dead(g, g->phil, i);
	i = 0;
	while (i < g->nb_phil)
		if (pthread_join(phil[i++].thread_id, NULL))
			return (42);
	if (mutex_destroy(g))
		return (42);
	return (0);
}

int	main(int ac, char **av)
{
	t_glob	g;

	if (ac != 5 && ac != 6)
		return (error("Invalid # of arg"));
	if (init_all(av, &g))
		return (error("Parsing or init issue") && !mutex_destroy(&g));
	if (philo(&g))
		return (error("Couldn't create threads") && !mutex_destroy(&g));
	return (0);
}