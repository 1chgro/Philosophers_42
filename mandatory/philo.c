#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	size_t	current_time;
	
	pthread_mutex_lock(&philo->table->meal_lock);
	if (philo->table->death_flag)
	{
		pthread_mutex_unlock(&philo->table->meal_lock);
		return ;
	}
	current_time = time_get() - philo->table->start_time;
	printf("%zu %d %s\n", current_time, philo->id, status);
	pthread_mutex_unlock(&philo->table->meal_lock);
}

int should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_lock);
	if (philo->table->death_flag)
	{
		pthread_mutex_unlock(&philo->table->meal_lock);
		return (1);
	}
	if (philo->table->must_eat_count != -1 && \
		philo->num_of_meals >= philo->table->must_eat_count)
	{
		pthread_mutex_unlock(&philo->table->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->meal_lock);
	return (0);
}

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

void *monitor(void *arg)
{
	printf("hello\n");
	return (void *)0;
}
int start_dinning(t_table *table)
{
	int i;
	pthread_t monitor_thread;
	
	i = 0;
	while(i < table->num_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine, &table->philos[i]) != 0)
			return (ft_putstr_fd("Error: creating threads\n", 2), 0);
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

int main(int ac, char **av)
{
	t_table table;

	if (ac != 5 && ac != 6)
		return (ft_putstr_fd("Error: Wrong num of args\n", 2), 1);
	if (!check_input(av))
		return (1);
	if (!initialize_all(av, &table))
		return (printf("init Error\n"), 1);
	if (table.num_of_philos == 1)
	{
		handle_one_philo(&table);
		destroy_mutexes(&table);
		return (0);
	}
	start_dinning(&table);
	printf("hello\n");

	destroy_mutexes(&table);
	return (0);
}
