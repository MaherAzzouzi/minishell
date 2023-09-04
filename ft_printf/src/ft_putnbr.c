/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:48:05 by snagat            #+#    #+#             */
/*   Updated: 2021/12/04 01:24:33 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n, int *count)
{
	
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		count++;
		return ;
	}
	if (n < 10 && n >= 0)
	{
		ft_putchar('0' + n, count);
	}
	else if (n >= 10)
	{
		ft_putnbr(n / 10, count);
		ft_putnbr(n % 10, count);
	}
	else
	{
		ft_putchar('-', count);
		ft_putnbr(-n, count);
	}
}