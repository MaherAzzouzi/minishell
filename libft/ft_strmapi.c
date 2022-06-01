/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 21:15:46 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 14:30:55 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*map;
	size_t	i;

	if (!s)
		return (0);
	len = ft_strlen(s);
	map = (char *)malloc((len + 1) * sizeof(char));
	if (!map)
	{
		return (0);
	}
	i = 0;
	while (i < len)
	{
		map[i] = (*f)(i, s[i]);
		i++;
	}
	map[i] = 0;
	return (map);
}
