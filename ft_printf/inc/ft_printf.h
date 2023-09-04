/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 01:19:00 by snagat            #+#    #+#             */
/*   Updated: 2021/12/04 01:50:59 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H 
# define FT_PRINTF_H

#include <unistd.h>
#include <stdarg.h>

int	    ft_printf(const char *str, ...);
void	ft_putchar(char c, int *count);
void	ft_cnvert_hex(int n, char *base, int *count);
void	ft_putnbr(int n, int *count);
void	ft_putnbr_uns(unsigned int n, int *count);
void	ft_putstr(char *str, int *count);

#endif