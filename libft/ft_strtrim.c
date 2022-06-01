/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 07:31:37 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 14:29:10 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_finish(void)
{
	char	*p;

	p = (char *)malloc(sizeof(char) * 1);
	if (p == 0)
		return (0);
	p[0] = 0;
	return (p);
}

static int	trim_first(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (ft_is_in_set(s1[i], set))
			i++;
		else
			break ;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	size_t	len;
	char	*p;

	if (!s1 || !set)
		return (0);
	i = trim_first(s1, set);
	len = ft_strlen(s1);
	j = len - 1;
	while (j >= 0)
	{
		if (ft_is_in_set(s1[j], set))
			j--;
		else
			break ;
	}
	if (i > j)
		return (ft_finish());
	p = (char *)malloc(sizeof(char) * (j - i + 2));
	if (p == 0)
		return (0);
	ft_memcpy(p, &s1[i], j - i + 1);
	p[j - i + 1] = 0;
	return (p);
}
