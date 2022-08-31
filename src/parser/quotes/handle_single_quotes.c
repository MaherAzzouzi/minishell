/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:12:35 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 22:48:12 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	n_check_cur_head(t_lnode **head, t_lnode *current, t_lnode *prev,
		t_lnode *node)
{
	if (current == *head)
	{
		*head = current->next;
		(*head)->next = node;
	}
	else
	{
		prev->next = current->next;
		prev->next->next = node;
	}
}

void	join_cmd_with_quotes(t_lnode **head)
{
	t_lnode	*current;
	t_lnode	*node;
	t_lnode	*prev;
	t_lnode	*tmp;

	prev = NULL;
	current = *head;
	while (current)
	{
		if (current && current->next && current->next->next
			&& get_token(current) == CMD && (get_token(current->next) == SGLQT
				|| get_token(current->next) == DBLQT)
			&& get_token(current->next->next) == CMD)
		{
			node = ft_new_node_lex(CMD, get_cmd(current));
			n_check_cur_head(head, current, prev, node);
			set_cmd(node, ft_strjoin(get_cmd(node),
					get_cmd(current->next->next), 2));
			tmp = current->next->next;
			node->next = tmp->next;
			free(tmp);
		}
		prev = current;
		current = current->next;
	}
}
