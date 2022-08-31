/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:51:56 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 23:21:37 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_variable_length(char *p)
{
	char	*q;
	char	*t;

	if (p[0] != '$')
		return (FAIL);
	*p++ = '\xff';
	if (p[0] == '\xfe' || (*p == '$' || *p == '?') || (ft_isdigit(*p)))
		return (1);
	q = p;
	while (*p != 0)
	{
		t = p;
		while (ft_isalnum(*p))
			p++;
		while (*p == '_')
			p++;
		if (*p == '\xfe')
		{
			p++;
			break ;
		}
		if (t == p)
			break ;
	}
	return (p - q);
}

char	*return_env(char *p)
{
	char	*env;
	int		len;

	len = get_env_variable_length(p);
	env = (char *)malloc((len + 1) * sizeof(char));
	if (env == NULL)
		exit(-1);
	ft_memcpy(env, p + 1, len);
	env[len] = 0;
	return (env);
}

char	*remove_char(char *p, char c)
{
	int	i;
	int	j;

	i = 0;
	while (p[i])
	{
		if (p[i] == c)
		{
			j = i + 1;
			while (p[i] != 0)
			{
				p[i] = p[j];
				i++;
				j++;
			}
			p[i] = 0;
			i = -1;
		}
		i++;
	}
	return (p);
}

char	*n_expand_an_array_having_dlr(char *result, char *env,
		char *q, t_exec_struct *exec_s)
{
	if (env[0] == '\xfe' && env[1] == 0)
	{
		result = ft_strjoin(result, get_env(env, exec_s, 0), 2);
		result = ft_strjoin(result, q + ft_strlen(env) + 1, 0);
	}
	else if (strchr(env, '\xfe'))
	{
		env[ft_strlen(env) - 1] = 0;
		result = ft_strjoin(result, get_env(env, exec_s, 0), 2);
		result = ft_strjoin(result, q + ft_strlen(env) + 2, 0);
	}
	else
	{
		result = ft_strjoin(result, get_env(env, exec_s, 0), 2);
		result = ft_strjoin(result, q + ft_strlen(env) + 1, 0);
	}
	return (result);
}

char	*n_expand_an_array_having_dlr2(char *result, char *p)
{
	if (result)
	{
		replace(result, '\xff', '$');
		remove_char(result, '\xfe');
		return (result);
	}
	else
	{
		replace(p, '\xff', '$');
		remove_char(p, '\xfe');
		return (p);
	}
}
