/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parenthesis_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:03:29 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 19:04:16 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lnode	*find_next_right_par_or_eol(t_lnode *start)
{
	while (1)
	{
		if (get_token(start) == RIGHT_PAR
			|| get_token(start) == EOL
			|| get_token(start) == AND
			|| get_token(start) == OR
			|| get_token(start) == PIPE)
			return (start);
		start = start->next;
	}
	return (NULL);
}

char	*get_only_parenthesis_content(t_lnode *open_p, t_lnode *closing_p)
{
	char	*p;

	p = ft_strndup(open_p->parenthesis_start + 1,
			closing_p->parenthesis_start - open_p->parenthesis_start - 1);
	return (p);
}
