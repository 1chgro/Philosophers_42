/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olachgue <olachgue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:16:02 by olachgue          #+#    #+#             */
/*   Updated: 2025/03/09 02:17:29 by olachgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	valid_arg(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+')
		i++;
	while (s[i])
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
		ft_putstr_fd(ERR_INPUT, 2);
		return (0);
	}
	value = ft_atoi(s);
	if (value <= 0)
	{
		ft_putstr_fd(ERR_INPUT, 2);
		return (0);
	}
	return (1);
}

int	check_input(char **s)
{
	if (!parse_arg(s[1]) || !parse_arg(s[2]) || \
	!parse_arg(s[3]) || !parse_arg(s[4]))
		return (0);
	if (s[5] && !parse_arg(s[5]))
		return (0);
	return (1);
}
