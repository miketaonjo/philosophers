/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:01:58 by mcloarec          #+#    #+#             */
/*   Updated: 2022/12/07 17:02:54 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_philo_eat_bis(t_table *table, t_philo *philo)
{
	if (table->n_philo != 2)
	{
		if (pthread_mutex_lock(&(table->fork[philo->fork_2])) != 0)
			return (-1);
		ft_printf_mutex(table, philo, "has taken a fork");
		ft_printf_mutex(table, philo, "is eating");
		if (pthread_mutex_lock(&(table->time)) != 0)
			return (-1);
		philo->lst_eat = ft_gettimeofday(table);
		if (pthread_mutex_unlock(&(table->time)) != 0)
			return (-1);
		if (ft_time_pass(table, table->tte) != 0)
			return (-1);
		if (pthread_mutex_lock(&(table->var)) != 0)
			return (-1);
		philo->n_meal++;
		if (pthread_mutex_unlock(&(table->var)) != 0)
			return (-1);
		if (pthread_mutex_unlock(&(table->fork[philo->fork_2])) != 0)
			return (-1);
	}
	return (0);
}

int	ft_philo_eat(t_table *table, t_philo *philo)
{
	if (pthread_mutex_lock(&(table->fork[philo->fork_1])) != 0)
		return (-1);
	ft_printf_mutex(table, philo, "has taken a fork");
	if (ft_philo_eat_bis(table, philo) != 0)
		return (-1);
	if (pthread_mutex_unlock(&(table->fork[philo->fork_1])) != 0)
		return (-1);
	return (0);
}

int	ft_pattern(t_table *table, t_philo *philo)
{
	while (ft_verif_stop(table) != 1)
	{
		if (ft_philo_eat(table, philo) != 0)
			return (-1);
		if (philo->n_meal == table->total_meal)
		{
			if (pthread_mutex_lock(&(table->var)) != 0)
				return (-1);
			table->finish_eat++;
			if (pthread_mutex_unlock(&(table->var)) != 0)
				return (-1);
		}
		ft_printf_mutex(table, philo, "is sleeping");
		if (ft_time_pass(table, table->tts) != 0)
			return (-1);
		ft_printf_mutex(table, philo, "is thinking");
	}
	return (0);
}

void	*ft_thread(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = (t_table *)philo->table;
	if (philo->id % 2 == 0)
	{
		ft_printf_mutex(table, philo, "is thinking");
		if (ft_time_pass(table, table->tte) != 0)
			return (NULL);
	}
	if (ft_pattern(table, philo) != 0)
		return (NULL);
	return (0);
}

int	ft_start_thread(t_table *table, t_philo *philo)
{
	int		i;

	i = 1;
	table->start = ft_gettimenow();
	while (i < table->n_philo)
	{	
		philo[i].lst_eat = ft_gettimeofday(table);
		if (pthread_create(&(philo[i].thread), NULL,
				ft_thread, &(philo[i])) != 0)
			return (-1);
		i++;
	}
	ft_check_time(table, philo);
	i = 1;
	while (i < table->n_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	ft_free_philos(table, philo);
	return (0);
}
