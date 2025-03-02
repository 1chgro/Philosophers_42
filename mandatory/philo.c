#include "philo.h"

void init_args(char **av, t_table *table)
{
	table->num_of_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->must_eat_count = -1;
	if (av[5])
		table->must_eat_count = ft_atoi(av[5]);
}

int init_forks(t_table *table)
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
			return (free(table->forks), 0);
		i++;
	}
	return (1);
}

int init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->num_of_philos);
	if (!table->philos)
		return (free(table->forks), 0);
	i = 0;
	while (i < table->num_of_philos)
	{
		table->philos[i].id = i;
		table->philos[i].num_of_meals = 0;
		table->philos[i].last_meal = 0;
		table->philos[i].is_dead = 0;
		table->philos[i].is_eating = 0;
		table->philos[i].is_sleeping = 0;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->num_of_philos];
		i++;
	}
	return (1);
}


int init(char **av, t_table *table)
{
	init_args(av, table);
	if (!init_forks(table))
		return (0);
	if (!init_philos(table))
		return (0);
	return (1);
}
void *fun(void *arg)
{
	printf("hello\n");
	return (void *)0;
}

int main(int ac, char **av)
{
	t_table table;

	if (ac != 5 && ac != 6)
		return (ft_putstr_fd("Error: Wrong num of args\n", 2), 1);
	if (!check_input(av))
		return (1);
	if (!init(av, &table))
		return (printf("init Error\n"), 1);
	

	return (0);
}
