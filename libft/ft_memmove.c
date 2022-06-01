/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:23:23 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 14:03:12 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;
	char		*d_end;
	const char	*s_end;

	d = dst;
	s = src;
	if (dst == 0 && src == 0)
		return (0);
	if (s > d)
	{
		while (len--)
			*d++ = *s++;
	}
	else
	{
		d_end = d + len - 1;
		s_end = s + len - 1;
		while (len--)
		{
			*d_end-- = *s_end--;
		}
	}
	return (dst);
}
