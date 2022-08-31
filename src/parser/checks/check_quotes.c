/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:43:58 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 22:48:12 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	ft_check_quotes(t_lnode *head, t_token dlm)
{
	t_lnode	*current;

	current = head;
	while (current)
	{
		if (get_token(current) == dlm
			&& current->next && current->next->next
			&& get_token(current->next) == CMD
			&& is_empty(get_cmd(current->next))
			&& get_token(current->next->next) == EOL)
			return (FAIL);
		current = current->next;
	}
	return (SUCCESS);
}
