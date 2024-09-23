/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_funcoes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mausilva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:24:44 by mausilva          #+#    #+#             */
/*   Updated: 2024/05/23 19:24:46 by mausilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putnbr(int n, int *num_char)
{
	if (n == -2147483648)
		ft_putstr("-2147483648", num_char);
	else if (n < 0)
	{
		ft_putchar('-', num_char);
		n = -n;
		ft_putnbr(n, num_char);
	}
	else if (n > 9)
	{
		ft_putnbr((n / 10), num_char);
		ft_putchar((n % 10) + 48, num_char);
	}
	else
		ft_putchar(n + 48, num_char);
}

void	ft_putnbr_u(unsigned int n, int *num_char)
{
	unsigned int	nb;

	nb = n;
	if (nb < 10)
		ft_putchar(nb + 48, num_char);
	if (nb > 9)
	{
		ft_putnbr(nb / 10, num_char);
		ft_putnbr(nb % 10, num_char);
	}
}

void	ft_hexa_low(unsigned long long low, int *num_char)
{
	char	*base;

	base = "0123456789abcdef";
	if (low > 15)
		ft_hexa_low(low / 16, num_char);
	ft_putchar(base[low % 16], num_char);
}

void	ft_hexa_upper(unsigned long long upper, int *num_char)
{
	char	*base;

	base = "0123456789ABCDEF";
	if (upper > 15)
		ft_hexa_upper(upper / 16, num_char);
	ft_putchar(base[upper % 16], num_char);
}

void	ft_ptr(void *ptr, int *num_char)
{
	unsigned long	addr;

	addr = (unsigned long)ptr;
	if (!ptr)
		ft_putstr("(nil)", num_char);
	else
	{
		ft_putstr("0x", num_char);
		ft_hexa_low(addr, num_char);
	}
}
