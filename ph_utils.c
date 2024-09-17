/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:18:18 by gkomba            #+#    #+#             */
/*   Updated: 2024/09/17 12:35:18 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

static int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_find_alpha_in_list(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (ft_isalpha(*str))
			i = 1;
		str++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	resul;

	sign = 1;
	resul = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
		sign *= -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= 48 && *nptr <= 57)
	{
		resul = resul * 10 + *nptr - '0';
		nptr++;
	}
	return (resul * sign);
}
