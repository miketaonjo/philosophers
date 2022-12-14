/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:01:32 by mcloarec          #+#    #+#             */
/*   Updated: 2022/12/07 17:02:26 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_philo(t_table *table, t_philo **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * table->n_philo);
	if (!(philo))
	{
		ft_free_table(table);
		return (-1);
	}
	i = 1;
	while (i < table->n_philo)
	{
		(*philo)[i].table = table;
		(*philo)[i].id = i;
		(*philo)[i].fork_1 = (*philo)[i].id;
		if (i == table->n_philo - 1)
			(*philo)[i].fork_2 = 1;
		else
			(*philo)[i].fork_2 = (*philo)[i].id + 1;
		(*philo)[i].n_meal = 0;
		i++;
	}
	return (0);
}

int	ft_init_mutex(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&(table->time), NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(table->death), NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(table->var), NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(table->msg), NULL) != 0)
		return (-1);
	table->fork = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!(table->fork))
		return (-1);
	i = 1;
	while (i < table->n_philo)
	{
		if (pthread_mutex_init(&(table->fork[i]), NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_check_correct_time(t_table *table, char **argv)
{
	table->ttd = ft_atoll(argv[2]);
	table->tte = ft_atoll(argv[3]);
	if (table->tte == 0)
		return (-1);
	table->tts = ft_atoll(argv[4]);
	if (table->tts == 0)
		return (-1);
	return (0);
}

int	ft_init_table(t_table *table, int argc, char **argv)
{
	table->n_philo = (ft_atoll(argv[1]) + 1);
	if (table->n_philo > 201 || table->n_philo < 2)
		return (-1);
	if (ft_check_correct_time(table, argv) != 0)
		return (-1);
	if (argc == 6)
	{
		table->total_meal = ft_atoll(argv[5]);
		if (table->total_meal == 0)
			return (-1);
	}
	else
		table->total_meal = -1;
	if (table->n_philo <= 0 || table->ttd < 0 || table->tte < 0
		|| table->tts < 0 || (argc == 6 && table->total_meal <= 0))
		return (-1);
	table->finish_eat = 0;
	table->stop = 0;
	table->print = 0;
	if (ft_init_mutex(table) == -1)
		return (-1);
	return (0);
}
