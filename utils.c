/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:01:45 by mcloarec          #+#    #+#             */
/*   Updated: 2022/12/07 09:36:04 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_printf_death(t_table *table, t_philo *philo, int i, char *s)
{
	long long	now;

	now = ft_gettimeofday(table);
	if (pthread_mutex_lock(&(table->msg)) != 0)
		return (-1);
	printf("%lld %d %s\n", now, philo[i].id, s);
	if (pthread_mutex_unlock(&(table->msg)) != 0)
		return (-1);
	if (pthread_mutex_lock(&(table->var)) != 0)
		return (-1);
	table->print++;
	if (pthread_mutex_unlock(&(table->var)) != 0)
		return (-1);
	return (0);
}

int	ft_verif_print(t_table *table)
{
	int	i;

	if (pthread_mutex_lock(&(table->var)) != 0)
		return (-1);
	i = table->print;
	if (pthread_mutex_unlock(&(table->var)) != 0)
		return (-1);
	return (i);
}

int	ft_printf_mutex(t_table *table, t_philo *philo, char *s)
{
	long long	now;

	now = ft_gettimeofday(table);
	if (pthread_mutex_lock(&(table->msg)) != 0)
		return (-1);
	if (ft_verif_print(table) != 1)
		printf("%lld %d %s\n", now, philo->id, s);
	if (pthread_mutex_unlock(&(table->msg)) != 0)
		return (-1);
	return (0);
}

long long	ft_gettimeofday(t_table *table)
{
	struct timeval	tv;
	long long int	time;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	time = time - table->start;
	return (time);
}

int	ft_atoll(char *s)
{
	long long int	result;
	int				sign;
	int				len;

	result = 0;
	sign = 1;
	len = 0;
	while (*s == '\t' || *s == '\n' || *s == '\v'
		|| *s == '\f' || *s == '\r' || *s == ' ')
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '+' || *s == '-')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		result = result * 10 + (*s - 48);
		len++;
		if (result < 0 || len > 19)
			return (-1);
		s++;
	}
	return (result * sign);
}
