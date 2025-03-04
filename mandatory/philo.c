#include "philo.h"

void	handle_one_philo(t_table *table)
{
	printf("0 1 %s\n", FORK_MSG);
	usleep(table->time_to_die * 1000);
	printf("%d 1 %s\n", table->time_to_die, DEAD_MSG);
}

int	start_dining(t_table *table)
{
	pthread_t	monitor_thread;
	int			i;

	table->start_time = time_get();
	i = 0;
	while (i < table->num_of_philos)
	{
		table->philos[i].last_meal = table->start_time;
		if (pthread_create(&table->philos[i].thread, NULL, routine, &table->philos[i]) != 0)
			return (ft_putstr_fd(ERR_THREAD, 2), 0);
		i++;
	}
	
	if (pthread_create(&monitor_thread, NULL, monitoring, table) != 0)
		return (ft_putstr_fd(ERR_THREAD, 2), 0);
		
	i = 0;
	while (i < table->num_of_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (1);
}

int main(int ac, char **av)
{
	t_table table;

	if (ac != 5 && ac != 6)
		return (ft_putstr_fd(ERR_ARGS, 2), 1);
	if (!check_input(av))
		return (1);
	if (!initialize_all(av, &table))
		return (ft_putstr_fd(ERR_INIT, 2), 1);
	if (table.num_of_philos == 1)
	{
		handle_one_philo(&table);
		destroy_mutexes(&table);
		return (0);
	}
	start_dining(&table);
	destroy_mutexes(&table);
	return (0);
}
