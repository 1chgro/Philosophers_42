#include "philo.h"

void	handle_one_philo(t_table *table)
{
	printf("0 1 %s\n", FORK_MSG);
	usleep(table->time_to_die * 1000);
	printf("%d 1 %s\n", table->time_to_die, DEAD_MSG);
}

void print_status(t_philo *philo, char *status)
{
	size_t current_time;

	pthread_mutex_lock(&philo->table->meal_lock);
	if (philo->table->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->table->meal_lock);
		return ;
	}
	current_time = time_get() - philo->table->start_time;
	printf("%zu %d %s\n", current_time, philo->id, status);
	pthread_mutex_unlock(&philo->table->meal_lock);
}

void philo_think(t_philo *philo)
{
	print_status(philo, THINK_MSG);
}
void philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEP_MSG);
	usleep(philo->table->time_to_sleep * 1000);
}

void philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(100);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, FORK_MSG);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, FORK_MSG);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	philo_eat(philo);
	philo_sleep(philo);
	philo_think(philo);
	return ((void *)(long)philo->id);
}

void *monitoring(void *arg)
{
	// printf("monitoring...\n");
	return ((void *)(long)0);
}
int start_dining(t_table *table)
{
	pthread_t monitor_thread;
	int i = 0;
	while(i < table->num_of_philos)
	{
		pthread_create(&table->philos[i].thread, NULL, routine, &table->philos[i]);
		i++;
	}
	i = 0;
	pthread_create(&monitor_thread, NULL, monitoring, NULL);
	while(i < table->num_of_philos)
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
		return (ft_putstr_fd(ERR_ARGS, 2), 1);
	if (!check_input(av))
		return (1);
	if (!initialize_all(av, &table))
		return (ft_putstr_fd(ERR_INIT, 2), 1);
	if (table.num_of_philos == 1)
	{
		handle_one_philo(&table);
		destroy_mutexes(&table);
		return (0);
	}
	start_dining(&table);
	destroy_mutexes(&table);
	return (0);
}
