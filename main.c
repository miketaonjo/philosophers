#include "philo.h"

long long	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_philo_start(t_table *table, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < table->nb_philo)
	{	
		philo[i].lst_eat = ft_get_time();
		if (pthread_create(&(philo[i].thread), NULL, ft_thread, &(philo[i])))
			return (1);
		i++;
	}
	ft_philo_check_finish(table, philo);
	i = 0;
	while (i < table->nb_philo)
		pthread_join(philo[i++].thread, NULL);
	ft_free_thread(table, philo);
	return (0);
}

int	ft_arg_init_mutex(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&(table->print), NULL))
		return (1);
	table->fork = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!(arg->fork))
		return (1);
	i = 0;
	while (i < arg->nb_philo)
	{
		if (pthread_mutex_init(&(table->fork[i]), NULL))
			return (1);
		i++;
	}
	return (0);
}

int	ft_arg_init(t_table *table, int argc, char **argv)
{
	table->nb_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->start_time = ft_get_time();
	if (table->nb_philo <= 0 || table->time_to_die < 0 || table->time_to_eat < 0
		|| table->time_to_sleep < 0)
	{
		return (5);
	}
	if (argc == 6)
	{
		table->eat_times = ft_atoi(argv[5]);
		if (table->eat_times <= 0)
			return (6);
	}
	if (ft_arg_init_mutex(table))
		return (1);
	return (0);
}

int	ft_philo_init(t_philo **philo, t_table *table)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * table->nb_philo);
	if (!(philo))
		return (1);
	while (i < table->nb_philo)
	{
		(*philo)[i].table = table;
		(*philo)[i].id = i;
		(*philo)[i].fork_l = i;
		(*philo)[i].fork_r = (i + 1) % table->nb_philo;
		(*philo)[i].lst_eat = ft_get_time();
		(*philo)[i].count_eat = 0;
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philo;
	int		errno;

	if (argc != 5 && argc != 6)
		return (print_error("error argc", 3));
	memset(&table, 0, sizeof(t_table));
	errno = ft_arg_init(&table, argc, argv);
	if (errno)
		return (print_error("error arg init", errno));
	errno = ft_philo_init(&philo, &table);
	if (errno)
		return (print_error("error philo init", errno));
	errno = ft_philo_start(&table, philo);
	if (errno)
		return (print_error("error philo start", errno));
	return (0);
}
