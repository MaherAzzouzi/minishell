/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:22:35 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 14:05:13 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_size;
	size_t	s_size;
	char	*d;
	size_t	r;
	size_t	i;

	d_size = 0;
	s_size = 0;
	d = dst;
	while (*d)
		d++;
	s_size = ft_strlen(src);
	d_size = ft_strlen(dst);
	r = min(d_size, dstsize) + s_size;
	if (d_size > dstsize || dstsize == 0)
		return (r);
	i = 0;
	while (i + d_size < dstsize - 1 && *src)
	{
		*d++ = *src++;
		i++;
	}
	*d = 0;
	return (r);
}
