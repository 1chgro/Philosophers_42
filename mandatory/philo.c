#include "philo.h"

size_t get_time(void)
{
	return (32);
}




int main(int ac, char **av)
{
	// atexit(f);
	t_table table;

	if (ac != 5 && ac != 6)
		return (ft_putstr_fd(ERR_ARGS, 2), 1);
	if (!check_input(av))
		return (1);
	if (!init_table(&table, av))
		return (ft_putstr_fd(ERR_INIT, 2), 1);
	// start_dining(&table);
	destroy_mutexes(&table);
	return (0);
}
