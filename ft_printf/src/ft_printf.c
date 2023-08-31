/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:49:48 by snagat            #+#    #+#             */
/*   Updated: 2021/12/04 01:51:11 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_type(char c, va_list args, int *count)
{
	if (c == '%')
		ft_putchar('%', count);
	if (c == 'c')
		ft_putchar(va_arg(args, int), count);
	if (c == 's')
		ft_putstr(va_arg(args, char *), count);
	if (c == 'd')
		ft_putnbr(va_arg(args, int), count);
	if (c == 'p')
		ft_putstr("0x", count);
		ft_cnvert_hex(va_arg(args, unsigned int),"0123456789abcdef", count);
	if (c == 'i')
		ft_putnbr(va_arg(args, int), count);
	if (c == 'u')
		ft_putnbr_uns(va_arg(args, unsigned int), count);
	if (c == 'x')
		ft_cnvert_hex(va_arg(args, unsigned int),"0123456789abcdef", count);
	if (c == 'X')
		ft_cnvert_hex(va_arg(args, unsigned int),"0123456789ABCDEF", count);
}

int	ft_printf(const char *str, ...)
{
	va_list args;
	va_start(args, str);
	int	i;
	int	count;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '%')
			check_type(str[++i], args, &count);
		else
			ft_putchar(str[i], &count);
	}
	va_end(args);
	return (count);	
}
