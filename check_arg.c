/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:05:40 by mcloarec          #+#    #+#             */
/*   Updated: 2022/12/03 10:30:09 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v')
		return (0);
	return (-1);
}

int	ft_check_if_nb(char *s)
{
	int	i;

	i = 0;
	while (ft_isspace(s[i]) == 0)
		i++;
	if (s[i] == '-')
		return (-1);
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		i++;
	while (ft_isspace(s[i]) == 0)
		i++;
	if (s[i] == '\0')
		return (0);
	return (-1);
}

int	ft_check_arg(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (-1);
	i = 1;
	while (argv[i])
	{
		if (*argv[i] == '\0')
			return (-1);
		else if (ft_check_if_nb(argv[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}
