#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

void	ft_putstr_fd(char *s, int fd);
int	ft_atoi(const char *str);
int	valid_arg(char *s);
int	parse_arg(char *s);
int	check_input(char **s);

#endif