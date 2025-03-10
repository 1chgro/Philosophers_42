/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olachgue <olachgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:20:15 by olachgue          #+#    #+#             */
/*   Updated: 2025/03/09 02:23:28 by olachgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo *philo, char *message)
{
	if (!philo->table->death_flag)
		printf("%zu %d %s\n", get_time() - \
		philo->table->start_time, philo->id, message);
}

int	check_death(t_table *table, int i)
{
	size_t	current_time;

	pthread_mutex_lock(&table->time_lock);
	current_time = get_time();
	if ((int)(current_time - table->philos[i].last_meal) > \
	table->time_to_die && !table->death_flag)
	{
		pthread_mutex_lock(&table->print_lock);
		printf("%zu %d %s\n", current_time - table->start_time, \
		table->philos[i].id, DEAD_MSG);
		table->death_flag = 1;
		pthread_mutex_unlock(&table->print_lock);
		pthread_mutex_unlock(&table->time_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->time_lock);
	return (0);
}

int	check_eating(t_table *table, int i)
{
	int	all_ate_enough;
	int	j;

	all_ate_enough = 0;
	pthread_mutex_lock(&table->eat_lock);
	if (table->must_eat_count > 0 && \
	table->philos[i].num_of_meals >= table->must_eat_count)
	{
		all_ate_enough = 1;
		j = -1;
		while (++j < table->num_of_philos && all_ate_enough)
			if (table->philos[j].num_of_meals < table->must_eat_count)
				all_ate_enough = 0;
		if (all_ate_enough)
		{
			pthread_mutex_lock(&table->print_lock);
			table->death_flag = 1;
			pthread_mutex_unlock(&table->print_lock);
		}
	}
	pthread_mutex_unlock(&table->eat_lock);
	return (all_ate_enough);
}

void	monitor(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!table->death_flag)
	{
		i = 0;
		while (i < table->num_of_philos)
		{
			if (check_eating(table, i) || check_death(table, i))
				return ;
			i++;
		}
		usleep(100);
	}
}
