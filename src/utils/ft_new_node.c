/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:44:52 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:45:36 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lnode	*ft_add_back_lex(t_lnode **head, e_token token, char *cmd)
{
	t_lnode	*node;
	t_lnode	*current;

	node = ft_new_node_lex(token, cmd);
	if (token == LEFT_PAR || token == RIGHT_PAR)
		node->parenthesis_start = cmd;
	current = *head;
	if (*head == NULL)
	{
		*head = node;
		return (*head);
	}
	while (current->next)
		current = current->next;
	current->next = node;
	node->next = NULL;
	return (*head);
}

t_lnode	*ft_new_node_lex(e_token token, char *cmd)
{
	t_lnode	*node;
	size_t	size;

	node = malloc(sizeof(t_lnode));
	if (!node)
		exit(1);
	if (token == CMD)
	{
		size = 0;
		while (cmd[size] && lexer_get_type(cmd[size], cmd[size + 1]) == CMD)
			size++;
		node->type.cmd = (char *)malloc((size + 1) * sizeof(char));
		ft_memcpy(node->type.cmd, cmd, size * sizeof(char));
		node->type.cmd[size] = '\0';
	}
	else
		node->type.cmd = NULL;
	node->type.token = token;
	node->next = NULL;
	return (node);
}
