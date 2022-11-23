#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
		return (putstr_error("Error argc", 3));
	if (ft_init_table(&table, argc, argv) != 0)
		putstr_error("Error init table"));
	if (ft_init_philo(&table, &philo) != 0)
		putstr_error("Error init philo"));
	if (ft_start_thread(&table, philo) != 0)
		putstr_error("Error start thread"));
	return (0);
}
