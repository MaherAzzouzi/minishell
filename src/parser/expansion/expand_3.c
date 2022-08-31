/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:55:12 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 22:48:12 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*case_of_one_char_dlr(char *p, t_exec_struct *exec_s)
{
	if (ft_strcmp(p, "$?") == 0 || ft_strcmp(p, "$$") == 0)
	{
		p = get_env(p + 1, exec_s, 0);
		return (p);
	}
	else if (ft_strcmp(p, "\xff?") == 0 || ft_strcmp(p, "\xff\xff") == 0)
	{
		replace(p, '\xff', '$');
		return (ft_strdup(p));
	}
	return (NULL);
}

void	n_expand_one_node(t_parsing_node *node,
		t_exec_struct *exec_s, char *p)
{
	int	i;

	i = 0;
	while (node->cmd.argv[i])
	{
		p = case_of_one_char_dlr(node->cmd.argv[i], exec_s);
		if (p == NULL)
		{
			p = expand_an_array_having_dlr(node->cmd.argv[i], exec_s);
			if (p != NULL)
				node->cmd.argv[i] = p;
		}
		else
		{
			free(node->cmd.argv[i]);
			node->cmd.argv[i] = p;
		}
		i++;
	}
}

void	expand_one_node(t_parsing_node *node, t_exec_struct *exec_s)
{
	char	*p;

	if (node->cmd.cmd == NULL || node->cmd.cmd[0] == 0)
		return ;
	p = case_of_one_char_dlr(node->cmd.cmd, exec_s);
	if (p == NULL)
	{
		p = expand_an_array_having_dlr(node->cmd.cmd, exec_s);
		if (p != NULL)
			node->cmd.cmd = p;
	}
	else
	{
		free(node->cmd.cmd);
		node->cmd.cmd = p;
	}
	n_expand_one_node(node, exec_s, p);
}

t_lnode	*n_consolidate_dlr_with_cmd(t_lnode *current, t_lnode **head,
		int *is_current_changed)
{
	t_lnode	*p;

	p = NULL;
	current->next->type.cmd = ft_strjoin("$", current->next->type.cmd, 1);
	if (current == (*head))
	{
		p = *head;
		*head = (*head)->next;
		current = current->next;
		free_lexer_node(p);
	}
	else
	{
		p = *head;
		while (p->next != current)
			p = p->next;
		p->next = current->next;
		free_lexer_node(current);
		current = p->next;
	}
	*is_current_changed = 1;
	return (current);
}

t_lnode	*n_consolidate_dlr_with_cmd_2(t_lnode **head, t_exec_struct *exec_s,
			t_lnode *current, int *is_current_changed)
{
	if (get_token(current->next) == DLR)
	{
		current = case_of_one_char_dollar(head, current, exec_s, 0);
		*is_current_changed = 1;
	}
	else if (get_token(current->next) == CMD)
		current = n_consolidate_dlr_with_cmd(current,
				head, is_current_changed);
	else
	{
		current->type.token = CMD;
		current->type.cmd = ft_strdup("$");
	}
	return (current);
}
