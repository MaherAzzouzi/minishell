/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_uns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 01:05:15 by snagat            #+#    #+#             */
/*   Updated: 2021/12/04 01:42:15 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_uns(unsigned int n, int *count)
{
	
	if (n < 10 && n >= 0)
	{
		ft_putchar('0' + n, count);
	}
	else if (n >= 10)
	{
		ft_putnbr_uns(n / 10, count);
		ft_putnbr_uns(n % 10, count);
	}
}
