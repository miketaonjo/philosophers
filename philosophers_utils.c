/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:40:36 by mcloarec          #+#    #+#             */
/*   Updated: 2022/12/07 09:33:57 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_verif_stop(t_table *table)
{
	int	i;

	if (pthread_mutex_lock(&(table->var)) != 0)
		return (-1);
	i = table->stop;
	if (pthread_mutex_unlock(&(table->var)) != 0)
		return (-1);
	return (i);
}

int	ft_verif_eat(t_table *table)
{
	int	i;

	if (pthread_mutex_lock(&(table->var)) != 0)
		return (-1);
	i = table->finish_eat;
	if (pthread_mutex_unlock(&(table->var)) != 0)
		return (-1);
	return (i);
}

int	ft_time_pass(t_table *table, long long action)
{
	long long		now;
	long long		time;

	now = ft_gettimeofday(table);
	time = action + now;
	if (action >= 50)
	{
		while ((time / 100) > (ft_gettimeofday(table) / 100))
		{
			if (ft_verif_stop(table) == 1)
				break ;
			usleep(1000);
		}
	}
	while (time > ft_gettimeofday(table))
	{
		if (ft_verif_stop(table) == 1)
			break ;
		if (usleep(100) != 0)
			return (-1);
	}
	return (0);
}

int	ft_check_death(t_table *table, t_philo *philo, long long result)
{
	int			i;
	long long	now;

	i = 1;
	while (i < table->n_philo)
	{
		now = ft_gettimeofday(table);
		if (pthread_mutex_lock(&(table->time)) != 0)
			return (-1);
		result = now - philo[i].lst_eat;
		if (pthread_mutex_unlock(&(table->time)) != 0)
			return (-1);
		if (result >= table->ttd)
		{
			ft_printf_death(table, philo, i, "died");
			if (pthread_mutex_lock(&(table->var)) != 0)
				return (-1);
			philo[i].table->stop = 1;
			if (pthread_mutex_unlock(&(table->var)) != 0)
				return (-1);
			break ;
		}
		i++;
	}
	return (0);
}

int	ft_check_time(t_table *table, t_philo *philo)
{
	long long	result;

	result = 0;
	if (pthread_mutex_lock(&(table->death)) != 0)
		return (-1);
	while (table->stop != 1)
	{
		if (ft_verif_eat(table) == (table->n_philo - 1))
		{
			if (pthread_mutex_lock(&(table->var)) != 0)
				return (-1);
			table->stop = 1;
			if (pthread_mutex_unlock(&(table->var)) != 0)
				return (-1);
		}
		if (ft_check_death(table, philo, result) != 0)
			return (-1);
		usleep(500);
	}
	if (pthread_mutex_unlock(&(table->death)) != 0)
		return (-1);
	return (0);
}
