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

void init_forks(t_table *table)
{
    int i;
    if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
        return ;
    table->forks = malloc(sizeof(pthread_mutex_t) *(table->num_of_philos));
    if (!table->forks)
        return ;
    i = 0;
    while(i < table->num_of_philos)
    {
        if (pthread_mutex_init(&table->forks[i], NULL) != 0)
        {
            free(table->forks);
            return ;
        }
        i++;
    }
}

void init_philos(t_table *table)
{
    
}

void init_all(char **av, t_table *table)
{
    init_args(av, table);
    init_forks(table);
    init_philos(table);
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
    init_all(av, &table);


    return (0);
}