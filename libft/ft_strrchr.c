/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:13:33 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 14:11:59 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	tf;
	int		i;

	tf = (char)c;
	i = 0;
	while (s[i])
		i++;
	if (tf == 0)
		return ((char *)(&s[i]));
	while (i >= 0)
	{
		if (s[i] == tf)
			return ((char *)(&s[i]));
		i--;
	}
	return (0);
}
