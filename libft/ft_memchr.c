/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:36:58 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 14:17:02 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	tf;
	size_t			i;
	unsigned char	*src;

	tf = (unsigned char)c;
	src = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (src[i] == tf)
			return ((void *)(&src[i]));
		i++;
	}
	return (0);
}
