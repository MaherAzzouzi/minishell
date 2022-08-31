/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:18:58 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 21:10:06 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_var_env
{
	t_envp	*head;
	t_envp	*current;
	char	*s;
	char	*var;
	int		i;
	int		flag;
}	t_var_env;

static void	print_env(t_var_env *var, t_envp **env)
{
	var->head = *env;
	while (var->head)
	{
		if (ft_egale_len(var->head->str) != -1)
			ft_printf("%s\n", var->head->str);
		var->head = var->head->next;
	}
}

static void	replace_env_var(t_var_env *var, t_envp **env, t_parsing_node *node)
{
	var->current = *env;
	while (var->current)
	{
		var->var = ft_strndup(var->current->str,
				ft_egale_len(var->current->str));
		if (!ft_strcmp(var->s, var->var)
			&& var->current->str[ft_egale_len(var->current->str)] == '=')
		{
			var->flag = 1;
			free(var->current->str);
			var->current->str = ft_strdup(node->cmd.argv[var->i]);
		}
		free(var->var);
		var->current = var->current->next;
	}
	free(var->s);
}

static int	loop_for_newenv(t_var_env *var, t_parsing_node *node, t_envp **env)
{
	var->i = 1;
	var->flag = 0;
	while (node->cmd.argv[var->i])
	{
		if (ft_egale_len(node->cmd.argv[var->i]) != -1
			&& node->cmd.argv[var->i][0] != '=')
			var->s = ft_strndup(node->cmd.argv[var->i],
					ft_egale_len(node->cmd.argv[var->i]));
		else
		{
			ft_putstr_fd("No such file or directory\n", 2);
			exit_status_fail();
			return (-1);
		}
		replace_env_var(var, env, node);
		if (var->flag == 0)
			new_env(env, node->cmd.argv[var->i]);
		var->i++;
	}
	return (0);
}

int	ft_env(t_parsing_node *node, t_envp **env)
{
	t_var_env	var;

	if (node->cmd.argv[1] == NULL)
		print_env(&var, env);
	else
	{
		if (loop_for_newenv(&var, node, env) == -1)
			return (-1);
		print_env(&var, env);
	}
	exit_status_success();
	return (0);
}
