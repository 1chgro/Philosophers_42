/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olachgue <olachgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:53:42 by olachgue          #+#    #+#             */
/*   Updated: 2025/03/13 02:02:57 by olachgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->table->print_lock);
	philo_print(philo, FORK_MSG);
	pthread_mutex_unlock(&philo->table->print_lock);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->table->print_lock);
	philo_print(philo, FORK_MSG);
	philo_print(philo, EAT_MSG);
	pthread_mutex_unlock(&philo->table->print_lock);
	pthread_mutex_lock(&philo->table->time_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->time_lock);
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->table->eat_lock);
	philo->num_of_meals++;
	pthread_mutex_unlock(&philo->table->eat_lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	philo_print(philo, SLEEP_MSG);
	pthread_mutex_unlock(&philo->table->print_lock);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	philo_print(philo, THINK_MSG);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	dining(t_philo *philo)
{
	if (philo->id % 2 == 0 || philo->id == philo->table->num_of_philos)
		ft_usleep(philo->table->time_to_eat / 2, philo->table);
	while (1)
	{
		if (should_stop(philo))
			break ;
		philo_eat(philo);
		if (should_stop(philo))
			break ;
		philo_sleep(philo);
		if (should_stop(philo))
			break ;
		philo_think(philo);
	}
	return ;
}

int	start_dining(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	if (table->num_of_philos == 1)
		return (handle_one_philo(table), 1);
	if (pthread_create(&monitor_thread, NULL, (void *)monitor, table) != 0)
		return (0);
	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, \
		(void *)dining, &table->philos[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return (0);
	return (1);
}
