#include "philo.h"

int	check_if_all_ate_enough(t_table *table)
{
	int	i;
	int	all_ate;

	if (table->must_eat_count == -1)
		return (0);
		
	all_ate = 1;
	i = 0;
	pthread_mutex_lock(&table->eat_lock);
	while (i < table->num_of_philos)
	{
		if (table->philos[i].num_of_meals < table->must_eat_count)
		{
			all_ate = 0;
			break;
		}
		i++;
	}
	pthread_mutex_unlock(&table->eat_lock);
	return (all_ate);
}

int	check_if_died(t_philo *philo)
{
	size_t	current_time;
	
	pthread_mutex_lock(&philo->table->eat_lock);
	current_time = time_get();
	if ((current_time - philo->last_meal) >= (size_t)philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->table->eat_lock);
		pthread_mutex_lock(&philo->table->print_lock);
		printf("%zu %d %s\n", current_time - philo->table->start_time, 
			philo->id, DEAD_MSG);
		pthread_mutex_unlock(&philo->table->print_lock);
		pthread_mutex_lock(&philo->table->eat_lock);
		philo->table->death_flag = 1;
		pthread_mutex_unlock(&philo->table->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->eat_lock);
	return (0);
}

void	*monitoring(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->num_of_philos)
		{
			if (check_if_died(&table->philos[i]) || check_if_all_ate_enough(table))
			{
				pthread_mutex_lock(&table->eat_lock);
				table->death_flag = 1;
				pthread_mutex_unlock(&table->eat_lock);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

