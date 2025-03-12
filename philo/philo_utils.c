/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olachgue <olachgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:15:06 by olachgue          #+#    #+#             */
/*   Updated: 2025/03/12 02:10:40 by olachgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	total;

	sign = 1;
	total = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		total = total * 10 + (*str - '0');
		if (total > 2147483647)
			return (-1);
		str++;
	}
	return (total * sign);
}

void	destroy_mutexes(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->eat_lock);
	i = 0;
	if (table->forks)
	{
		i = 0;
		while (i < table->num_of_philos)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
		free(table->forks);
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->time_lock);
	pthread_mutex_destroy(&table->eat_lock);
	pthread_mutex_destroy(&table->death_lock);
	if (table->philos)
		free(table->philos);
}

int	ft_usleep(size_t time, t_table *table)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		pthread_mutex_lock(&table->death_lock);
		if (table->death_flag)
		{
			pthread_mutex_unlock(&table->death_lock);
			return (0);
		}
		pthread_mutex_unlock(&table->death_lock);
		usleep(100);
	}

	return (0);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
