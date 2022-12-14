/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 10:01:16 by mcloarec          #+#    #+#             */
/*   Updated: 2022/12/07 15:27:58 by mcloarec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	struct s_table	*table;
	int				id;
	int				fork_1;
	int				fork_2;
	long long		lst_eat;
	int				n_meal;
	pthread_t		thread;
}				t_philo;

typedef struct s_table
{
	int				n_philo;
	int				ttd;
	int				tte;
	int				tts;
	int				total_meal;
	long long		start;
	int				finish_eat;
	int				stop;
	int				print;
	pthread_mutex_t	var;
	pthread_mutex_t	death;
	pthread_mutex_t	time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	msg;
}				t_table;

/*init*/
int			ft_init_philo(t_table *table, t_philo **philo);
int			ft_init_mutex(t_table *table);
int			ft_init_table(t_table *table, int argc, char **argv);

/*check_arg*/

int			ft_isspace(char c);
int			ft_check_if_nb(char *s);
int			ft_check_arg(int argc, char **argv);

/*philosophers*/
int			ft_philo_eat_bis(t_table *table, t_philo *philo);
int			ft_philo_eat(t_table *table, t_philo *philo);
int			ft_pattern(t_table *table, t_philo *philo);
void		*ft_thread(void *arg);
int			ft_start_thread(t_table *table, t_philo *philo);

/*philosophers_utils*/
int			ft_verif_stop(t_table *table);
int			ft_time_pass(t_table *table, long long action);
int			ft_check_death(t_table *table, t_philo *philo, long long result);
int			ft_check_time(t_table *table, t_philo *philo);

/*utils*/
int			ft_printf_death(t_table *table, t_philo *philo, int i, char *s);
int			ft_printf_mutex(t_table *table, t_philo *philo, char *s);
long long	ft_gettimeofday(t_table *table);
int			ft_atoll(char *s);
long long	ft_gettimenow(void);

/*free*/
void		ft_free_philos(t_table *table, t_philo *philo);
void		ft_free_table(t_table *table);

#endif
