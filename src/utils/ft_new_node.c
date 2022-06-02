/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:43:29 by snagat            #+#    #+#             */
/*   Updated: 2022/06/02 11:11:13 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lnode	*ft_add_back_lex(t_lnode **head, e_token token, char *cmd)
{
	t_lnode	*node;
	t_lnode	*current;

	node = ft_new_node_lex(token, cmd);
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
	size_t size;

	node = malloc(sizeof(t_lnode));
	if (!node)
		exit(1);
	if (token == CMD)
	{
		size = 0;
		while (lexer_get_type(cmd[size], cmd[size + 1]) == CMD)
			size++;
		node->type.cmd = (char *)malloc((size + 1) * sizeof(char));
		ft_memcpy(node->type.cmd, cmd, size);
		node->type.cmd[size] = '\0';
		//printf("[%s] added to the linked list!\n", node->type.cmd);
	}
	else
	{
		node->type.cmd = NULL;
		//printf("[%s] added to the linked list!\n", enum_to_str(token));
	}
	node->type.token = token;
	node->next = NULL;
	return (node);
}


