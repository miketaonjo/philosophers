void	ft_thread(void *arg)
{
	if (arg->id % 2 = 0)
	{
		if (usleep(500) != 0)
		{
			ft_free_philos(table, philo);
			return ;
		}
	}
	else
	{
		if (usleep(1000) != 0)
		{
			ft_free_philos(table, philo);
			return ;
		}
	}
}

int	ft_start_thread(t_table *table, t_philo *philo)
{
	int		i;
	struct timeval tv;

	i = 0;
	while (i < table->nb_philo)
	{
		if (gettimeofday(&tv, NULL) == -1)
		{
			putstr_error("Error timeval");
			return (-1);
		}
		philo[i].lst_eat = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
		if (pthread_create(&(philo[i].thread), NULL, ft_thread, &(philo[i])) != 0)
		{
			ft_free_philos(table, philo);
		}
		i++;
	}
	ft_philo_check_finish(table, philo);
	i = 0;
	while (i < table->nb_philo)
		pthread_join(philo[i++].thread, NULL);
	ft_free_thread(table, philo);
	return (0);
}
