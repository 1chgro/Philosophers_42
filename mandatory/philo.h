#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>


typedef struct s_philo
{
    int id;
    pthread_t thread;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    int is_dead;
    int is_sleeping;
    int is_eating;
    int last_meal;
    int num_of_meals;
}t_philo;


typedef struct s_table
{
    int num_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_count;
    int death_flag;
    size_t start_time;
    pthread_mutex_t meal_lock;
    // pthread_mutex_t sleep_lock;
    pthread_mutex_t *forks;
    t_philo *philos;
}   t_table;

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		valid_arg(char *s);
int		parse_arg(char *s);
int		check_input(char **s);

#endif