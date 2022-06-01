/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:08:14 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 14:22:02 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_whitespace(char c)
{
	return ((c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
			|| c == '\r'));
}

static int	ignore_whitespaces_return_index(const char *str, int *sign)
{
	int	i;

	*sign = 1;
	i = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '-')
	{
		*sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	result = 0;
	i = ignore_whitespaces_return_index(str, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i++] - '0';
	}
	return (result * sign);
}
