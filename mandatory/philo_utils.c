#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}

}

int	ft_atoi(const char *str)
{
	int		sign;
	long	total;

	sign = 1;
	total = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		total = total * 10 + (*str - '0');
		if (total > 2147483647)
			return (-1);
		str++;
	}
	return (total * sign);
}


void destroy_mutexes(t_table *table)
{
    int i;

    pthread_mutex_destroy(&table->eat_lock);
    i = 0;
    if (table->forks)
    {
        i = 0;
        while (i < table->num_of_philos)
        {
            pthread_mutex_destroy(&table->forks[i]);
            i++;
        }
    }
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->time_lock);
	pthread_mutex_destroy(&table->eat_lock);
    if (table->forks)
		free(table->forks);
    if (table->philos)
		free(table->philos);
}
