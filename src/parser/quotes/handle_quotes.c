/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:05:41 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 19:05:43 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	order_quotes(t_lnode **head)
{
	t_lnode	*current;

	current = *head;
	while (current)
	{
		if (get_token(current) == SGLQT)
		{
			current = handle_single_quote(current);
			if (current == (t_lnode *)-1)
				return (FAIL);
		}
		else if (get_token(current) == DBLQT)
		{
			current = handle_double_quote(current);
			if (current == (t_lnode *)-1)
				return (FAIL);
		}
		else
			current = current->next;
	}
	return (SUCCESS);
}

void	fix_after_expansion(t_lnode *head)
{
	t_lnode	*current;
	int		dblqt_flag;
	int		sglqt_flag;

	dblqt_flag = 1;
	sglqt_flag = 1;
	current = head;
	while (get_token(current) != EOL)
	{
		if (!dblqt_flag && !sglqt_flag)
			return ;
		if (get_token(current) == DBLQT && dblqt_flag)
		{
			handle_double_quote(head);
			current = head;
			dblqt_flag = 0;
		}
		else if (get_token(current) == SGLQT && sglqt_flag)
		{
			handle_single_quote(head);
			current = head;
			sglqt_flag = 0;
		}
		current = current->next;
	}
}
