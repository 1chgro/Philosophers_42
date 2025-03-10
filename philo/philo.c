/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olachgue <olachgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:11:17 by olachgue          #+#    #+#             */
/*   Updated: 2025/03/10 22:33:35 by olachgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_one_philo(t_table *table)
{
	printf("%zu %d %s\n", get_time() - table->start_time, 1, FORK_MSG);
	usleep(table->time_to_die * 1000);
	printf("%zu %d %s\n", get_time() - table->start_time, 1, DEAD_MSG);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if (!check_input(av))
			return (1);
		if (!init_table(&table, av))
			return (ft_putstr_fd(ERR_INIT, 2), 1);
		if (!start_dining(&table))
			return (destroy_mutexes(&table), 1);
		destroy_mutexes(&table);
	}
	else
		return (ft_putstr_fd(ERR_ARGS, 2), 1);
	return (0);
}
