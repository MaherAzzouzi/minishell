/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 07:14:01 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 14:32:05 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_recur(unsigned int number, int fd)
{
	int	reminder;
	int	left;

	reminder = number % 10;
	left = number / 10;
	if (left != 0)
		ft_putnbr_recur(left, fd);
	ft_putchar_fd('0' + reminder, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
	{
		nb = -n;
		ft_putchar_fd('-', fd);
	}
	else
	{
		nb = n;
	}
	ft_putnbr_recur(nb, fd);
}
