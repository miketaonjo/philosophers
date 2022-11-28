void	*ft_thread(void *argv)
{
	t_arg		*arg;
	t_philo		*philo;

	philo = argv;
	arg = philo->arg;
	if (philo->id % 2)
		usleep(1000);
	else
		usleep(500);
	while (!arg->finish)
	{
		ft_philo_action(arg, philo);
		if (arg->eat_times == philo->eat_count)
		{
			arg->finished_eat++;
			break ;
		}
		ft_philo_printf(arg, philo->id, "is sleeping");
		ft_pass_time((long long)arg->time_to_sleep, arg);
		ft_philo_printf(arg, philo->id, "is thinking");
	}
	return (0);
}

void	ft_free_thread(t_arg *arg, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < arg->philo_num)
		pthread_mutex_destroy(&(arg->forks[i++]));
	free(philo);
	free(arg->forks);
	pthread_mutex_destroy(&(arg->print));
}

void	ft_philo_check_finish(t_arg *arg, t_philo *philo)
{
	int			i;
	long long	now;

	while (!arg->finish)
	{
		if ((arg->eat_times != 0) && (arg->philo_num == arg->finished_eat))
		{
			arg->finish = 1;
			break ;
		}
		i = 0;
		while (i < arg->philo_num)
		{
			now = ft_get_time();
			if ((now - philo[i].last_eat_time) >= arg->time_to_die)
			{
				ft_philo_printf(arg, i, "died");
				arg->finish = 1;
				break ;
			}
			i++;
		}
	}
}



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
