#include "philo.h"

void	handle_one_philo(t_table *table)
{
	printf("0 1 %s\n", FORK_MSG);
	usleep(table->time_to_die * 1000);
	printf("%d 1 %s\n", table->time_to_die, DEAD_MSG);
}
void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, FORK_MSG);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, FORK_MSG);
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->is_eating = 1;
	philo->last_meal = time_get();
	pthread_mutex_unlock(&philo->table->meal_lock);
	print_status(philo, EAT_MSG);
	philo->num_of_meals++;
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->table->meal_lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_think(t_philo *philo)
{
	print_status(philo, THINK_MSG);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEP_MSG);
	usleep(philo->table->time_to_sleep * 1000);
}
