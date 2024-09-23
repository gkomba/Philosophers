/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mausilva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:02:51 by mausilva          #+#    #+#             */
/*   Updated: 2024/05/23 19:02:54 by mausilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putchar(char c, int *num_char)
{
	write(1, &c, 1);
	(*num_char)++;
}

void	ft_putstr(char *s, int *num_char)
{
	int	i;

	i = 0;
	if (!s)
		ft_putstr("(null)", num_char);
	else
	{
		while (s[i])
		{
			ft_putchar(s[i], num_char);
			i++;
		}
	}
}

void	ft_veri(const char *s, va_list lst, int *num_char)
{
	if (*s == '%')
		ft_putchar('%', num_char);
	else if (*s == 'c')
		ft_putchar(va_arg(lst, int), num_char);
	else if (*s == 's')
		ft_putstr(va_arg(lst, char *), num_char);
	else if (*s == 'd')
		ft_putnbr(va_arg(lst, int), num_char);
	else if (*s == 'i')
		ft_putnbr(va_arg(lst, int), num_char);
	else if (*s == 'u')
		ft_putnbr_u(va_arg(lst, unsigned int), num_char);
	else if (*s == 'p')
		ft_ptr(va_arg(lst, void *), num_char);
	else if (*s == 'x')
		ft_hexa_low((long)va_arg(lst, unsigned int), num_char);
	else if (*s == 'X')
		ft_hexa_upper((long)va_arg(lst, unsigned int), num_char);
}

int	ft_printf(const char *s, ...)
{
	va_list	lst;
	int		num_char;

	num_char = 0;
	va_start(lst, s);
	while (*s)
	{
		if (*s == '%')
			ft_veri(++s, lst, &num_char);
		else
			ft_putchar(*s, &num_char);
		s++;
	}
	va_end(lst);
	return (num_char);
}
#include <stdio.h>


int	main()
{
	int	i = 3;
	printf("%p", &i);
	return (0);
}
