#include "philo.h"

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
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
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