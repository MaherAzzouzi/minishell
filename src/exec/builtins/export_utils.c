/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:19:51 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:19:53 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_new_env
{
	t_envp	*curr;
	char	*s;
	char	*var;
	int		t;
}	t_new_env;

static void	cor_(t_new_env *new, char *str)
{
	new->var = ft_strndup(new->curr->str, ft_egale_len(new->curr->str));
	if (!ft_strcmp(new->s, new->curr->str) && check_equal(str) == 1)
	{
		new->t = 1;
		free(new->curr->str);
		new->curr->str = ft_strdup(str);
	}
	else if (!ft_strcmp(new->s, new->curr->str))
		new->t = 1;
	else if (!ft_strcmp(new->s, new->var)
		&& new->curr->str[ft_egale_len(new->curr->str)] == '='
		&& check_equal(str) == 2)
	{
		new->t = 1;
		new->curr->str = ft_strjoin(new->curr->str, &ft_strchr(str, '=')[1], 0);
	}
	else if (!ft_strcmp(new->s, new->var)
		&& new->curr->str[ft_egale_len(new->curr->str)] == '=')
	{
		new->t = 1;
		free(new->curr->str);
		new->curr->str = ft_strdup(str);
	}
	free(new->var);
}

int	check_new_env(char *str, t_envp **env)
{
	t_new_env	new;

	new.curr = *env;
	new.t = 0;
	set_ar_w_e_o_n(&new.s, str);
	while (new.curr)
	{
		cor_(&new, str);
		new.curr = new.curr->next;
	}
	free(new.s);
	return (new.t);
}

int	check_equal(char *str)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			x = i;
			break ;
		}
		i++;
	}
	if (x > 0)
	{
		if (ft_isalnum(str[x - 1]))
			return (1);
		else if (str[x - 1] == '+')
			return (2);
		else
			return (-1);
	}
	return (3);
}

int	check_export_syntax(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 || (check_equal(str) == -1))
	{
		return (-1);
	}
	else
		return (1);
}
