/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:42:20 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/25 21:26:22 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

# define HEX_LOWERCASE "0123456789abcdef"
# define HEX_UPPERCASE "0123456789ABCDEF"

int		ft_putchar(char c);
int		ft_putstr(char *str);
void	ft_putnbr_recur(unsigned int number);
int		ft_putnbr(int nb);
int		ft_putnbr_unsigned(int nb);
int		ft_print_hex(unsigned long long p);
int		is_valid_base(char *g_base);
void	ft_putnbr_base_helper(unsigned int nb, int l, char *b, int *ret);
void	ft_putnbr_base(unsigned int nbr, char *base, int *ret);
int		ft_printf(const char *format, ...);

#endif
