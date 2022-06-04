/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:34:17 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 14:27:14 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
char	*ft_strjoin(char const *s1, char const *s2, int flag)
{
	int		i;
	int		j;
	size_t	len;
	char	*p;

	if (!s1 || !s2)
		return (0);
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc((len + 1) * sizeof(char));
	if (p == 0)
		return (0);
	if (len == 0)
	{
		p[0] = 0;
		return (p);
	}
	j = 0;
	while (s1[i])
		p[j++] = s1[i++];
	j = 0;
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = 0;
	if (flag == 2)
	{
		free((void *)s1);
		free((void *)s2);
	}
	else if (flag == 1)
		free((void *)s2);
	else if (flag == 0)
		free((void *)s1);
	return (p);
}
