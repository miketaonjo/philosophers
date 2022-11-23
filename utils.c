void	ft_free_table(t_table *table)
{
	int	i;
	
	i = 0;
	if (!table)
		return ;
	if (table->fork != NULL)
	{
		free(table-<fork);
		table->fork = NULL;
	}
}

int	ft_atoll(char *s)
{
	long long	result;
	int		sign;

	result = 0;
	sign = 0;
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
		if (result < 0)
			return (-1);
		s++;
	}
	return (result * sign);
}
