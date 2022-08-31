/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tree_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:00:33 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 19:02:18 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_end_before_start(t_lnode *start, t_lnode *end)
{
	while (end && get_token(end) != EOL)
	{
		if (end == start)
			return (1);
		end = end->next;
	}
	return (0);
}

t_lnode	*get_end(t_lnode *head)
{
	while (get_token(head) != EOL)
		head = head->next;
	return (head);
}

t_lnode	*return_highest_priv(t_lnode *current, t_lnode *end)
{
	t_lnode	*p;
	int		flag;
	int		count;

	p = get_end(current);
	flag = 0;
	count = 0;
	while (current != end && get_token(current) != EOL)
	{
		if (get_token(current) == LEFT_PAR)
			count++;
		if (get_token(current) == PIPE && get_token(p) != AND
			&& flag == 0 && count == 0 && get_token(p) != OR)
		{
			p = current;
			flag = 1;
		}
		else if ((get_token(current) == AND || get_token(current) == OR)
			&& count == 0)
			p = current;
		if (get_token(current) == RIGHT_PAR)
			count--;
		current = current->next;
	}
	return (p);
}

t_lnode	*n_get_not_inside_p(t_lnode *current)
{
	int	count;

	count = 0;
	while (get_token(current) != EOL)
	{
		if (get_token(current) == LEFT_PAR)
			count++;
		else if (get_token(current) == RIGHT_PAR)
			count--;
		if ((get_token(current) == AND || get_token(current) == OR)
			&& count == 0)
			return (current);
		current = current->next;
	}
	return (current);
}

t_lnode	*stop_at_higher_priv(t_lnode *highest)
{
	t_lnode	*current;

	current = highest;
	if (get_token(highest) == PIPE)
		return (n_get_not_inside_p(current));
	else if (get_token(highest) == AND || get_token(highest) == OR)
	{
		current = current->next;
		return (n_get_not_inside_p(current));
	}
	else
		return (highest);
}
