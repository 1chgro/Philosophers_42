#include "philo.h"

void initialize_args(char **av, t_table *table)
{
	table->num_of_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->death_flag = 0;
	table->must_eat_count = -1;
	if (av[5])
		table->must_eat_count = ft_atoi(av[5]);
}

int initialize_forks(t_table *table)
{
	int i;
	if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
		return (0);
	table->forks = malloc(sizeof(pthread_mutex_t) *(table->num_of_philos));
	if (!table->forks)
		return (0);
	i = 0;
	while(i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			pthread_mutex_destroy(&table->meal_lock);
			return (free(table->forks), 0);
		}
		i++;
	}
	return (1);
}

int initialize_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->num_of_philos);
	if (!table->philos)
		return (destroy_mutexes(table), 0);
	i = 0;
	table->start_time = time_get();
	while (i < table->num_of_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].is_dead = 0;
		table->philos[i].is_eating = 0;
		table->philos[i].is_sleeping = 0;
		table->philos[i].last_meal = table->start_time;
		table->philos[i].num_of_meals = 0;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->num_of_philos];
		table->philos[i].table = table;

		i++;
	}
	return (1);
}

int initialize_all(char **av, t_table *table)
{
	initialize_args(av, table);
	if (!initialize_forks(table))
		return (0);
	if (!initialize_philos(table))
		return (0);
	return (1);
}