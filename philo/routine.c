
#include "philo.h"

int should_stop(t_philo *philo)
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

int check_death(t_table *table, int i)
{
	size_t current_time;

	pthread_mutex_lock(&table->time_lock);
	current_time = get_time();
	pthread_mutex_lock(&table->death_lock);
	if ( (current_time - table->philos[i].last_meal) > ((size_t)(table->time_to_die)) && !table->death_flag)
	{
		pthread_mutex_lock(&table->print_lock);
		printf("%zu %d %s\n", current_time - table->start_time, \
		table->philos[i].id, DEAD_MSG);
		pthread_mutex_unlock(&table->print_lock);
		table->death_flag = 1;
		pthread_mutex_unlock(&table->death_lock);
		pthread_mutex_unlock(&table->time_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->death_lock);
	pthread_mutex_unlock(&table->time_lock);
	return (0);
}

int check_all_ate(t_table *table, int i)
{
	int all_ate;
	int j;

	all_ate = 0;
	pthread_mutex_lock(&table->eat_lock);
	if (table->must_eat_count > 0 && table->philos[i].num_of_meals >= table->must_eat_count)
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


void monitor(t_table *table)
{
	int i;
	while(1)
	{
		pthread_mutex_lock(&table->death_lock);
		if (table->death_flag)
		{
			pthread_mutex_unlock(&table->death_lock);
			break ;
		}
		pthread_mutex_unlock(&table->death_lock);
		i = 0;
		while(i < table->num_of_philos)
		{
			if (check_death(table, i) || check_all_ate(table, i))
				return ;
			i++;
		}
		usleep(500);
	}
	return ;
}

void philo_eat(t_philo *philo)
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
	pthread_mutex_lock(&philo->table->eat_lock);
	philo->num_of_meals++;
	pthread_mutex_unlock(&philo->table->eat_lock);
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	philo_print(philo, SLEEP_MSG);
	pthread_mutex_unlock(&philo->table->print_lock);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}
void philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	philo_print(philo, THINK_MSG);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void dining(t_philo *philo)
{
	if (philo->id % 2 == 0 || philo->id == philo->table->num_of_philos)
		usleep(1000);
	while(1)
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
