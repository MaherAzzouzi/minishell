/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:42:06 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:43:27 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer_node(t_lnode *node)
{
	if (get_cmd(node))
		free(get_cmd(node));
	free(node);
}

void	free_list(t_lnode **head)
{
	t_lnode	*current;
	t_lnode	*tmp;

	current = *head;
	if (head == 0 || *head == 0)
		return ;
	while (current)
	{
		tmp = current;
		if (tmp->type.cmd)
			free(tmp->type.cmd);
		current = current->next;
		free(tmp);
	}
	*head = 0;
}

void	free_all(char *cmd, t_lnode *head, t_parsing_node *root)
{
	(void)head;
	free_list(&head);
	free_tree(root);
	free(cmd);
}
