void	ft_free_tab(t_table *table)
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
