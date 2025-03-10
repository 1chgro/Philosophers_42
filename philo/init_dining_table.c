/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dining_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olachgue <olachgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:18:30 by olachgue          #+#    #+#             */
/*   Updated: 2025/03/09 02:19:59 by olachgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].last_meal = table->start_time;
		table->philos[i].num_of_meals = 0;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = \
		&table->forks[(i + 1) % table->num_of_philos];
		table->philos[i].table = table;
		i++;
	}
}

int	init_philo_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_of_philos);
	if (!table->forks)
		return (0);
	while (i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (--i)
				pthread_mutex_destroy(&table->forks[i]);
			return (free(table->forks), 0);
		}
		i++;
	}
	table->philos = malloc(sizeof(t_philo) * table->num_of_philos);
	if (!table->philos)
		return (destroy_mutexes(table), 0);
	init_philo(table);
	return (1);
}

int	init_table(t_table *table, char **av)
{
	table->num_of_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->must_eat_count = -1;
	if (av[5])
		table->must_eat_count = ft_atoi(av[5]);
	table->death_flag = 0;
	table->start_time = get_time();
	if (pthread_mutex_init(&table->eat_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->time_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (0);
	if (!init_philo_forks(table))
		return (0);
	return (1);
}
