/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olachgue <olachgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:20:15 by olachgue          #+#    #+#             */
/*   Updated: 2025/03/11 22:50:27 by olachgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->table->death_lock);
	if (!philo->table->death_flag)
		printf("%zu %d %s\n", get_time() - \
		philo->table->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->table->death_lock);
}
