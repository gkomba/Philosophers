/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mausilva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:57:06 by mausilva          #+#    #+#             */
/*   Updated: 2024/05/23 19:02:06 by mausilva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdarg.h>

void	ft_putnbr(int n, int *num_char);
void	ft_ptr(void *ptr, int *num_char);
void	ft_putstr(char *s, int *num_char);
void	ft_putchar(char c, int *num_char);
void	ft_putnbr_u(unsigned int n, int *num_char);
void	ft_hexa_low(unsigned long long low, int *num_char);
void	ft_hexa_upper(unsigned long long upper, int *num_char);
void	ft_veri(const char *s, va_list lst, int *num_char);

int		ft_printf(const char *s, ...);

#endif
