/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:22:29 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:22:31 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_parsing_node *node, t_envp **env)
{
	t_envp	*export;
	t_envp	*current;

	export = exxport(env);
	ft_sort_export(export);
	current = export;
	if (node->cmd.argv[1] == NULL)
	{
		while (current)
		{
			p_(current->str, ft_egale_len(current->str));
			current = current->next;
		}
	}
	else
	{
		if (checking_new_env(node, env, export) == FAIL)
			return (FAIL);
	}
	free_env(&export);
	convert(*env);
	exit_status_success();
	return (SUCCESS);
}
