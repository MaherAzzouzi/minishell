/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:23:58 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 14:21:40 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == 0)
		return ((char *)(haystack));
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len && needle[j])
			j++;
		if (needle[j] == 0)
			return ((char *)(&haystack[i]));
		i++;
	}
	return (0);
}
