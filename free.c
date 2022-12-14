/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:29:48 by mcloarec          #+#    #+#             */
/*   Updated: 2022/12/07 17:03:05 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_philos(t_table *table, t_philo *philo)
{
	ft_free_table(table);
	free(philo);
}

void	ft_free_table(t_table *table)
{
	int	i;

	i = 1;
	while (i < table->n_philo)
	{
		if (pthread_mutex_destroy(&(table->fork[i])) != 0)
			return ;
		i++;
	}
	free(table->fork);
	if (pthread_mutex_destroy(&(table->time)) != 0)
		return ;
	if (pthread_mutex_destroy(&(table->death)) != 0)
		return ;
	if (pthread_mutex_destroy(&(table->var)) != 0)
		return ;
	if (pthread_mutex_destroy(&(table->msg)) != 0)
		return ;
}
