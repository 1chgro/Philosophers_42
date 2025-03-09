#include "philo.h"

size_t get_time(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
int	ft_usleep(size_t time, t_table *table)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		if (table->death_flag)
			return (0);
		usleep(100);
	}
	return (0);
}

void philo_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(&philo->table->print_lock);
    if (!philo->table->death_flag)
        printf("%zu %d %s\n", get_time() - philo->table->start_time, philo->id, FORK_MSG);
    pthread_mutex_unlock(&philo->table->print_lock);
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(&philo->table->print_lock);
    if (!philo->table->death_flag)
        printf("%zu %d %s\n", get_time() - philo->table->start_time, philo->id, FORK_MSG);
    pthread_mutex_unlock(&philo->table->print_lock);
    pthread_mutex_lock(&philo->table->print_lock);
    if (!philo->table->death_flag)
        printf("%zu %d %s\n", get_time() - philo->table->start_time, philo->id, EAT_MSG);
    pthread_mutex_unlock(&philo->table->print_lock);
    pthread_mutex_lock(&philo->table->eat_lock);
    philo->num_of_meals++;
    pthread_mutex_unlock(&philo->table->eat_lock);
    pthread_mutex_lock(&philo->table->time_lock);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->table->time_lock); 
    ft_usleep(philo->table->time_to_eat, philo->table);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->death_flag)
		printf("%zu %d %s\n", get_time() - philo->table->start_time, philo->id, SLEEP_MSG);
	pthread_mutex_unlock(&philo->table->print_lock);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

void philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_lock);
	if (!philo->table->death_flag)
		printf("%zu %d %s\n", get_time() - philo->table->start_time, philo->id, THINK_MSG);
	pthread_mutex_unlock(&philo->table->print_lock);
}

void dining(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 == 0 || philo->id ==  philo->table->num_of_philos)
		usleep(1000);
	while(!philo->table->death_flag)
	{
		philo_eat(philo);
		if (philo->table->must_eat_count > 0)
        {
            pthread_mutex_lock(&philo->table->eat_lock);
            if (philo->num_of_meals >= philo->table->must_eat_count)
            {
                pthread_mutex_unlock(&philo->table->eat_lock);
                break;
            }
            pthread_mutex_unlock(&philo->table->eat_lock);
        }
		philo_sleep(philo);
		philo_think(philo);
	}
}

int check_death(t_table *table, int i)
{
    pthread_mutex_lock(&table->time_lock);
    size_t current_time = get_time();
    
    if ((int)(current_time - table->philos[i].last_meal) > table->time_to_die && !table->death_flag)
    {
        pthread_mutex_lock(&table->print_lock);
        printf("%zu %d %s\n", current_time - table->start_time, table->philos[i].id, DEAD_MSG);
        table->death_flag = 1;
        pthread_mutex_unlock(&table->print_lock);
        pthread_mutex_unlock(&table->time_lock);
        return (1);
    }
    pthread_mutex_unlock(&table->time_lock);
    return (0);
}

int check_eating(t_table *table, int i)
{
    int all_ate_enough = 0;

    pthread_mutex_lock(&table->eat_lock);
    if (table->must_eat_count > 0 && table->philos[i].num_of_meals >= table->must_eat_count)
    {
        int j = 0;
        all_ate_enough = 1;
        while (j < table->num_of_philos)
        {
            if (table->philos[j].num_of_meals < table->must_eat_count)
            {
                all_ate_enough = 0;
                break;
            }
            j++;
        }
        if (all_ate_enough)
        {
            pthread_mutex_lock(&table->print_lock);
            table->death_flag = 1;
            pthread_mutex_unlock(&table->print_lock);
        }
    }
    pthread_mutex_unlock(&table->eat_lock);
	return (all_ate_enough);
}
void monitor(void *arg)
{
	t_table *table = (t_table *)arg;
	int i;

	while(!table->death_flag)
	{
		i = 0;
		while(i < table->num_of_philos)
		{
			if (check_eating(table, i) || check_death(table, i))
				return ;
			i++;
		}
		usleep(100);
	}
}

void handle_one_philo(t_table *table)
{
    printf("%zu %d %s\n", get_time() - table->start_time, 1, FORK_MSG);
    usleep(table->time_to_die * 1000);
    printf("%zu %d %s\n", get_time() - table->start_time, 1, DEAD_MSG);
}

int start_dining(t_table *table)
{
	int i;
	pthread_t monitor_thread;

	if (table->num_of_philos == 1)
			return (handle_one_philo(table), 1);
	if (pthread_create(&monitor_thread, NULL, (void *)monitor, table))
		return (0);
	i = 0;
	while(i < table->num_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, (void *)dining, &table->philos[i]) != 0)
			return (0);
		i++;
	}
	i = 0;
	while(i < table->num_of_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (0);
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
	if (!init_table(&table, av))
		return (ft_putstr_fd(ERR_INIT, 2), 1);
	if (!start_dining(&table))
		return (destroy_mutexes(&table), 1);
	destroy_mutexes(&table);
	return (0);
}
