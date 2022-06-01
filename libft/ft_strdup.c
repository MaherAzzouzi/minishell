/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:04:31 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 14:23:15 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		src_len;
	char	*p;
	int		i;

	src_len = 0;
	while (src[src_len])
		src_len++;
	p = (char *) malloc((src_len + 1) * sizeof(char));
	if (p == 0)
		return (0);
	i = 0;
	while (src[i])
	{
		p[i] = src[i];
		i++;
	}
	p[i] = 0;
	return (p);
}
