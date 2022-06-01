/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:27:06 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 14:10:37 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c_s1;
	unsigned char	c_s2;
	size_t			i;

	i = 0;
	c_s1 = *s1++;
	c_s2 = *s2++;
	while (c_s1 == c_s2 && i < n && (c_s1 != 0))
	{
		c_s1 = *s1++;
		c_s2 = *s2++;
		i++;
	}
	if (i == n)
	{
		return (0);
	}
	return (c_s1 - c_s2);
}
