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
int check_death(t_table *table, int i)
{

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
		usleep(1000);
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