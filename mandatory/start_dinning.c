#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
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
	return (NULL);
}
int	check_death(t_table *table, int i)
{
	pthread_mutex_lock(&table->meal_lock);
	if (!table->philos[i].is_eating && 
		(time_get() - table->philos[i].last_meal) > 
		(size_t)table->time_to_die)
	{
		printf("%zu %d %s\n", 
			time_get() - table->start_time, 
			table->philos[i].id, DEAD_MSG);
		table->death_flag = 1;
		pthread_mutex_unlock(&table->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->meal_lock);
	return (0);
}

int	check_all_ate(t_table *table)
{
	int	i;
	int	all_ate;
	
	if (table->must_eat_count == -1)
		return (0);
	
	all_ate = 1;
	i = 0;
	while (i < table->num_of_philos)
	{
		pthread_mutex_lock(&table->meal_lock);
		if (table->philos[i].num_of_meals < table->must_eat_count)
			all_ate = 0;
		pthread_mutex_unlock(&table->meal_lock);
		if (!all_ate)
			break ;
		i++;
	}
	return (all_ate);
}

void	*monitor(void *arg)
{
	t_table	*table;
	int		i;
	
	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->num_of_philos)
		{
			if (check_death(table, i))
				return (NULL);
			i++;
		}
		if (check_all_ate(table))
		{
			pthread_mutex_lock(&table->meal_lock);
			table->death_flag = 1;
			pthread_mutex_unlock(&table->meal_lock);
			return (NULL);
		}
	}
	return (NULL);
}

int start_dinning(t_table *table)
{
	int i;
	pthread_t monitor_thread;
	
	i = 0;
	while(i < table->num_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine, &table->philos[i]) != 0)
			return (ft_putstr_fd(ERR_THREAD, 2), 0);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, table) != 0)
	{
		ft_putstr_fd(ERR_THREAD, 2);
		return (0);
	}
	i = 0;
	while (i < table->num_of_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (1);
}