int	ft_init_philo(t_table *table, t_philo **philo)
{
	int	i;
	//struct timeval	tv;

	*philos = malloc(sizeof(t_philo) * table->n_philo);
	if (!(philo))
	{
		ft_free_table(table);
		return (-1);
	}
	i = 0;
	while (i < table->n_philo)
	{
		(*philo)[i].table = table;
		(*philo)[i].id = i;
		(*philo)[i].fork_1 = i;
		(*philo)[i].fork_2 = (i + 1) % table->nb_philo;
		/*if (gettimeofday(&tv, NULL) == -1)
		{
			putstr_error("Error timeval");
			return (-1);
		}
		(*philo)[i].lst_eat = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);*/
		(*philo)[i].count_eat = 0;
		i++;
	}
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
	while (i < table->n_philo)
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
	
	table->n_philo = ft_atoll(argv[1]);
	table->time_to_die = ft_atoll(argv[2]);
	table->time_to_eat = ft_atoll(argv[3]);
	table->time_to_sleep = ft_atoll(argv[4]);
	if (argc == 6)
		table->n_meal = ft_atoll(argv[5]);
	if (table->n_philo <= 0 || table->time_to_die < 0 || table->time_to_eat < 0
		|| table->time_to_sleep < 0 || table->n_meal <= 0)
		return (-1);
	if (gettimeofday(&tv, NULL) == -1)
	{
		putstr_error("Error timeval");
		return (-1);
	}
	table->start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	table->stop = -1;
	table->finish_eat = -1;
	if (ft_init_mutex(table) == -1)
		return (-1);
	return (0);
}
