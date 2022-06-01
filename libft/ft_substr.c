/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 07:34:17 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 14:24:56 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_alloc_right_size(size_t length, size_t len, unsigned int start)
{
	char	*p;

	if (start + len <= length)
		p = (char *)malloc((len + 1) * sizeof(char));
	else
		p = (char *)malloc((length - start + 1) * sizeof(char));
	if (p == 0)
		return (0);
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	length;

	if (!s)
		return (0);
	length = ft_strlen(s);
	if (start >= length)
	{
		p = (char *)malloc(sizeof(char));
		p[0] = 0;
		return (p);
	}
	p = ft_alloc_right_size(length, len, start);
	if (p == 0)
		return (0);
	i = 0;
	while (i < len && s[start])
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = 0;
	return (p);
}
