#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <sys/time.h>
# include <fcntl.h>

# define ERR_ARGS "Error: Wrong number of arguments\n"
# define ERR_INPUT "Error: Invalid input\n"
# define ERR_INIT "Error: Initialization failed\n"
# define ERR_THREAD "Error: Thread creation failed\n"

# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DEAD_MSG "died"


void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		valid_arg(char *s);
int		parse_arg(char *s);
int		check_input(char **s);

# endif