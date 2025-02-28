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

int valid_arg(char *s)
{
    int i;
    i = 0;
    while(s[i])
    {
        if (!(s[i] >= '0' && s[i] <= '9'))
            return (0);
        i++;
    }
    return (1);
}

int parse_arg(char *s)
{
    if (!valid_arg(s) || ft_atoi(s) == -1 || ft_atoi(s) == 0)
    {
        ft_putstr_fd("Error: Invalid Input\n", 2);
		return (0);
    }
    return (1);
}

int check_input(char **s)
{
    if (!parse_arg(s[1]) || !parse_arg(s[2]) || !parse_arg(s[3]) || !parse_arg(s[4]))
        return (0);
    if (s[5] && !parse_arg(s[5]))
        return (0);
    return (1);
}

int main(int ac, char **av)
{
    t_table table;

    if (ac != 5 && ac != 6)
    {
    }
        ft_putstr_fd("Error: Wrong number of arguments\n", 2);
        return (1);
    if (!check_input(av))
        return (1);
    return (0);
}