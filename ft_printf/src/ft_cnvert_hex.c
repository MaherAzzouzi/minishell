/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cnvert_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:30:29 by snagat            #+#    #+#             */
/*   Updated: 2021/12/04 01:41:28 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_cnvert_hex(int n, char *base, int *count)
{
		if (n <= 16)
			ft_putchar(base[n], count);
		else
		{
			ft_cnvert_hex(n / 16, base, count);
			ft_cnvert_hex(n % 16, base, count);	
		}
}
