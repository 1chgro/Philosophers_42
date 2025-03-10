/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olachgue <olachgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:11:58 by olachgue          #+#    #+#             */
/*   Updated: 2025/03/09 02:32:52 by olachgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

# define ERR_ARGS "Error: Wrong number of arguments\n"
# define ERR_INPUT "Error: Invalid input\n"
# define ERR_INIT "Error: Initialization failed\n"
# define ERR_THREAD "Error: Thread creation failed\n"

# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DEAD_MSG "died"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	size_t			last_meal;
	int				num_of_meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				death_flag;
	size_t			start_time;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_table;

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		valid_arg(char *s);
int		parse_arg(char *s);
int		check_input(char **s);
void	destroy_mutexes(t_table *table);
int		init_table(t_table *table, char **av);
size_t	get_time(void);
void	monitor(void *arg);
int		start_dining(t_table *table);
int		ft_usleep(size_t time, t_table *table);
void	philo_print(t_philo *philo, char *message);
void	handle_one_philo(t_table *table);

#endif