/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_quotes_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:08:41 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 21:10:06 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lnode	*handle_quote(t_lnode *head, e_token dlm)
{
	t_lnode	*current;
	t_lnode	*sg;
	t_lnode	*node;
	t_lnode	*p;

	current = head;
	node = ft_new_node_lex(CMD, "");
	sg = current;
	current = current->next;
	while (get_token(current) != dlm && get_token(current) != EOL)
	{
		norm_join_quote(current, node);
		current = current->next;
	}
	if (get_token(current) == EOL)
	{
		ft_printf("Can not find a %s ender!\n", convert_token(dlm));
		free_lexer_node(node);
		return ((t_lnode *)(-1));
	}
	p = sg->next;
	n_free_leaks(p, current);
	sg->next = node;
	node->next = current;
	return (current->next);
}

t_lnode	*check_sglqt_dblqt(t_lnode *current, t_lnode *node)
{
	while ((get_token(current) == SGLQT || get_token(current) == DBLQT))
	{
		if (get_token(current->next) == CMD)
		{
			set_cmd(node, ft_strjoin(get_cmd(node),
					get_cmd(current->next), 2));
			current = current->next->next;
		}
		else if ((get_token(current) == SGLQT
				|| get_token(current) == DBLQT)
			&& (get_token(current->next) == DBLQT
				|| get_token(current->next) == SGLQT))
			current = current->next;
		else if ((get_token(current) == SGLQT || get_token(current) == DBLQT)
			&& get_token(current->next) != CMD)
			break ;
		else if ((get_token(current) == SGLQT || get_token(current) == DBLQT))
			current = current->next;
	}
	return (current);
}

void	free_quotes_leaks(t_lnode *temp, t_lnode *current)
{
	t_lnode	*tm;

	while (temp != current)
	{
		tm = temp->next;
		free(temp);
		temp = tm;
	}
}

void	join_quotes(t_lnode *head)
{
	t_lnode	*p;
	t_lnode	*current;
	t_lnode	*temp;
	t_lnode	*node;

	current = head;
	while (current)
	{
		if (((get_token(current) == SGLQT || get_token(current) == DBLQT)
				&& get_token(current->next) == CMD))
		{
			node = ft_new_node_lex(CMD, "");
			p = current;
			current = check_sglqt_dblqt(current, node);
			temp = p->next;
			free_quotes_leaks(temp, current);
			p->next = node;
			node->next = current;
		}
		current = current->next;
	}
}

t_lnode	*handle_single_quote(t_lnode *head)
{
	return (handle_quote(head, SGLQT));
}
