#include "philo.h"

void	handle_one_philo(t_table *table)
{
	printf("0 1 %s\n", FORK_MSG);
	usleep(table->time_to_die * 1000);
	printf("%d 1 %s\n", table->time_to_die, DEAD_MSG);
}

int main(int ac, char **av)
{
	t_table table;

	if (ac != 5 && ac != 6)
		return (ft_putstr_fd(ERR_ARGS, 2), 1);
	if (!check_input(av))
		return (1);
	if (!initialize_all(av, &table))
		return (printf("init Error\n"), 1);
	if (table.num_of_philos == 1)
	{
		handle_one_philo(&table);
		destroy_mutexes(&table);
		return (0);
	}
	if (!start_dinning(&table))
	{
		destroy_mutexes(&table);
		return (1);
	}
	destroy_mutexes(&table);
	return (0);
}
