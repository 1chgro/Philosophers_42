#include "philo.h"

typedef struct s_table t_table;

typedef struct s_philosopher
{
    int             id;
    long long       last_meal_time;
    int             meals_eaten;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_table         *table;
}t_philosopher;

typedef struct s_table
{
    int num_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_count;
    size_t  start_time;
    t_philosopher *philosopher;
}   t_table;

int main(int ac, char **av)
{
    t_table table;

    if (ac != 5 && ac != 6)
        return (ft_putstr_fd("Error: Wrong num of args\n", 2), 1);
    if (!check_input(av))
        return (1);
    
    return (0);
}