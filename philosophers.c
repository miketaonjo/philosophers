int	ft_start(t_table *table, t_philo *philo)
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
