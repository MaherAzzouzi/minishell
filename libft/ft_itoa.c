/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 07:37:08 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 14:30:04 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_string_rev(char *s)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
		i++;
		j--;
	}
}

static char	*get_number_chunk(int n)
{
	int		count;
	char	*p;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n)
	{
		count++;
		n = n / 10;
	}
	p = (char *)malloc((count + 1) * sizeof(char));
	if (!p)
		return (0);
	return (p);
}

char	*ft_itoa(int n)
{
	char			*res;
	int				i;
	unsigned int	nb;

	res = get_number_chunk(n);
	if (!res)
		return (0);
	if (n < 0)
		nb = -n;
	else
		nb = n;
	i = 0;
	while (nb)
	{
		res[i] = (nb % 10) + '0';
		nb = nb / 10;
		i++;
	}
	if (n < 0)
		res[i++] = '-';
	if (n == 0)
		res[i++] = '0';
	res[i] = 0;
	ft_string_rev(res);
	return (res);
}
