/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:58:28 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 18:58:30 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	consolidate_dlr_with_cmd(t_lnode **head, t_exec_struct *exec_s)
{
	t_lnode	*current;
	int		is_current_changed;

	current = *head;
	while (current && get_token(current) != EOL)
	{
		is_current_changed = 0;
		if (get_token(current) == DLR)
			current = n_consolidate_dlr_with_cmd_2(head, exec_s,
					current, &is_current_changed);
		if (!is_current_changed)
			current = current->next;
	}
	combine_successive_cmds(*head);
}
