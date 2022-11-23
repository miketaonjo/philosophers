#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo
{
	struct s_arg	*table;
	int				id;
	int				fork_1;
	int				fork_2;
	long long		lst_eat;
	int				count_eat;
	pthread_t		thread;
}				t_philo;

typedef struct s_table
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meal;
	long long			start;
	int				stop;
	int				finish_eat;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
}				t_table;
