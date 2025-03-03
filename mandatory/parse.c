#include "philo.h"

int	valid_arg(char *s)
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

int	parse_arg(char *s)
{
	int	value;

	if (!valid_arg(s))
	{
		ft_putstr_fd("Error: Invalid input\n", 2);
		return (0);
	}
	value = ft_atoi(s);
	if (value <= 0)
	{
		ft_putstr_fd("Error: Invalid input\n", 2);
		return (0);
	}
	return (1);
}

int	check_input(char **s)
{
	if (!parse_arg(s[1]) || !parse_arg(s[2]) || !parse_arg(s[3]) || !parse_arg(s[4]))
		return (0);
	if (s[5] && !parse_arg(s[5]))
		return (0);
	return (1);
}