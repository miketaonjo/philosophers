#include "philo.h"

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

int	ft_init_mutex(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&(table->print), NULL) != 0)
		return (-1);
	table->fork = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!(table->fork))
		return (-1);
	i = 0;
	while (table->fork[i])
	{
		if (pthread_mutex_init(&(table->fork[i]), NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_init_table(t_table *table, int argc, char **argv)
{
	struct timeval	tv;
	
	table->n_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->n_meal = ft_atoi(argv[5]);
	if (table->n_philo <= 0 || table->time_to_die < 0 || table->time_to_eat < 0
		|| table->time_to_sleep < 0 || table->n_meal <= 0)
		return (-1);
	if (gettimeofday(&tv, NULL) == -1)
		putstr_error("Error timeval");
	table->start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	table->stop = -1;
	table->finish_eat = -1;
	if (ft_init_mutex(table) == -1)
		return (-1);
	return (0);
}

int	ft_init_philo(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * table->n_philo);
	if (!(philo))
		return (-1);
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
	t_philo	philo;

	if (argc != 5 && argc != 6)
		return (putstr_error("Error argc", 3));
	if (ft_init_table(&table, argc, argv) != 0)
		putstr_error("Error init table"));
	if (ft_init_philo(&philo, &table) != 0)
		putstr_error("Error init philo"));
	ret = ft_philo_start(&table, philo);
	if (ret)
		return (print_error("error philo start", errno));
	return (0);
}
