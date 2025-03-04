#include "philo.h"

void philo_think(t_philo *philo)
{
	print_status(philo, THINK_MSG);
}
void philo_sleep(t_philo *philo)
{
	print_status(philo, SLEEP_MSG);
	usleep(philo->table->time_to_sleep * 1000);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, FORK_MSG);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, FORK_MSG);
	print_status(philo, EAT_MSG);
	pthread_mutex_lock(&philo->table->eat_lock);
	philo->last_meal = time_get();
	philo->num_of_meals++;
	pthread_mutex_unlock(&philo->table->eat_lock);
	
	usleep(philo->table->time_to_eat * 1000);
	
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

int	check_death_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->eat_lock);
	if (philo->table->death_flag == 1)
	{
		pthread_mutex_unlock(&philo->table->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->eat_lock);
	return (0);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->table->time_to_eat * 1000);
	while (!check_death_flag(philo))
	{
		philo_eat(philo);
		if (philo->table->must_eat_count != -1 && 
			philo->num_of_meals >= philo->table->must_eat_count)
			break;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
