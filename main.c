/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:00:30 by mcloarec          #+#    #+#             */
/*   Updated: 2022/12/07 15:28:23 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_gettimenow(void)
{
	struct timeval	start;
	long long		time;

	if (gettimeofday(&start, NULL) == -1)
		return (-1);
	time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return (time);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philo;

	if (ft_check_arg(argc, argv) != 0)
	{
		printf("Error arg\n");
		return (-1);
	}
	if (ft_init_table(&table, argc, argv) != 0)
	{
		printf("Error init table\n");
		return (-1);
	}
	if (ft_init_philo(&table, &philo) != 0)
	{
		printf("Error init philo\n");
		return (-1);
	}
	if (ft_start_thread(&table, philo) != 0)
	{
		printf("Error thread\n");
		ft_free_philos(&table, philo);
		return (-1);
	}
	return (0);
}
