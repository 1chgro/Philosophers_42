/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olachgue <olachgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:20:15 by olachgue          #+#    #+#             */
/*   Updated: 2025/03/12 22:39:50 by olachgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->table->death_lock);
	if (!philo->table->death_flag)
		printf("%zu %d %s\n", get_time() - philo->table->start_time, \
		philo->id, message);
	pthread_mutex_unlock(&philo->table->death_lock);
}

int	should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_lock);
	if (philo->table->death_flag)
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->death_lock);
	return (0);
}

int	check_death(t_table *table, int i)
{
	size_t	current_time;

	pthread_mutex_lock(&table->time_lock);
	current_time = get_time();
	pthread_mutex_lock(&table->death_lock);
	if ((current_time - table->philos[i].last_meal) > \
	((size_t)(table->time_to_die)) && !table->death_flag)
	{
		printf("%zu %d %s\n", current_time - table->start_time, \
		table->philos[i].id, DEAD_MSG);
		table->death_flag = 1;
		pthread_mutex_unlock(&table->death_lock);
		pthread_mutex_unlock(&table->time_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->death_lock);
	pthread_mutex_unlock(&table->time_lock);
	return (0);
}

int	check_all_ate(t_table *table, int i)
{
	int	all_ate;
	int	j;

	all_ate = 0;
	pthread_mutex_lock(&table->eat_lock);
	if (table->must_eat_count > 0 && \
	table->philos[i].num_of_meals >= table->must_eat_count)
	{
		all_ate = 1;
		j = -1;
		while (++j < table->num_of_philos && all_ate)
			if (table->philos[j].num_of_meals < table->must_eat_count)
				all_ate = 0;
		if (all_ate)
		{
			pthread_mutex_lock(&table->death_lock);
			table->death_flag = 1;
			pthread_mutex_unlock(&table->death_lock);
		}
	}
	pthread_mutex_unlock(&table->eat_lock);
	return (all_ate);
}

void	monitor(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->num_of_philos)
		{
			if (check_death(table, i) || check_all_ate(table, i))
				return ;
			i++;
		}
		usleep(1000);
	}
	return ;
}
