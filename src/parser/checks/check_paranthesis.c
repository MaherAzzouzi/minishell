/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paranthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:44:35 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 18:47:03 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_left_of_left_p(t_lnode *head)
{
	t_lnode	*current;

	current = head;
	while (get_token(current) != EOL)
	{
		current = return_lp(current);
		if (current == NULL)
			break ;
		if (check_left(head, current) == FAIL)
			return (FAIL);
		current = current->next;
	}
	return (SUCCESS);
}

int	is_red(t_lnode *node)
{
	e_token	t;

	t = node->type.token;
	return (t == DLMI || t == APPND || t == REDRI || t == REDRO);
}

int	check_right_part(t_lnode *head)
{
	t_lnode	*current;

	current = head;
	while (get_token(current) != EOL)
	{
		if (get_token(current) == RIGHT_PAR)
		{
			current = current->next;
			current = ignore_spaces_ret(current);
			if (get_token(current) == EOL)
				return (SUCCESS);
			if (get_token(current) != PIPE
				&& get_token(current) != AND
				&& get_token(current) != OR
				&& get_token(current) != EOL
				&& get_token(current) != RIGHT_PAR
				&& !is_red(current))
				return (FAIL);
		}
		else
			current = current->next;
	}
	return (SUCCESS);
}

int	check_left_par(t_lnode *head)
{
	if (check_empty_para(head) == FAIL
		|| check_if_balanced(head) == FAIL
		|| check_left_of_left_p(head) == FAIL
		|| check_right_part(head) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
