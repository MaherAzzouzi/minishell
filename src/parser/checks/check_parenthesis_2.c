/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parenthesis_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:47:13 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 22:48:12 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_para(t_lnode *head)
{
	t_lnode	*current;

	current = head;
	while (get_token(current) != EOL)
	{
		if (get_token(current) == LEFT_PAR)
		{
			current = current->next;
			current = ignore_spaces_ret(current);
			if (get_token(current) == EOL)
				return (FAIL);
			if (get_token(current) == RIGHT_PAR)
				return (FAIL);
		}
		current = current->next;
	}
	return (SUCCESS);
}

int	check_if_balanced(t_lnode *head)
{
	t_lnode	*current;
	int		count;
	int		flag;

	current = head;
	count = 0;
	flag = SUCCESS;
	while (get_token(current) != EOL)
	{
		if (get_token(current) == LEFT_PAR)
			count++;
		else if (get_token(current) == RIGHT_PAR)
			count--;
		if (count < 0)
		{
			flag = FAIL;
			break ;
		}
		current = current->next;
	}
	if (count != 0)
		flag = FAIL;
	return (flag);
}

t_lnode	*return_lp(t_lnode *head)
{
	t_lnode	*current;

	current = head;
	while (get_token(current) != EOL)
	{
		if (get_token(current) == LEFT_PAR)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	check_left(t_lnode *head, t_lnode *lp)
{
	t_token	t;

	t = PIPE;
	while (head != lp)
	{
		if (get_token(head) != SPC)
			t = get_token(head);
		head = head->next;
	}
	if (t == PIPE || t == OR || t == AND || t == LEFT_PAR)
		return (SUCCESS);
	return (FAIL);
}
