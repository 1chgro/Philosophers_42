#include "philo_bonus.h"

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (!check_input(av))
			return (1);
	}
	else
		return (ft_putstr_fd(ERR_ARGS, 2), 1);
	return (0);
}