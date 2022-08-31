/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_quotes_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:06:55 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 19:12:53 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cnvrt_tknv2(e_token token)
{
	if (token == PIPE)
		return ("|");
	else if (token == SPC)
		return (" ");
	else if (token == AND)
		return ("&&");
	else if (token == OR)
		return ("||");
	else if (token == CMD)
		return ("CMD");
	else if (token == EOL)
		return ("EOL");
	else if (token == DLR)
		return ("$");
	else if (token == LEFT_PAR)
		return ("(");
	else if (token == RIGHT_PAR)
		return (")");
	return (NULL);
}

char	*convert_token(e_token token)
{
	if (token == SGLQT)
		return ("'");
	else if (token == DBLQT)
		return ("\"");
	else if (token == REDRO)
		return (">");
	else if (token == REDRI)
		return ("<");
	else if (token == DLMI)
		return ("<<");
	else if (token == APPND)
		return (">>");
	return (cnvrt_tknv2(token));
}

int	count_token(t_lnode *head, t_lnode *current, e_token t)
{
	int	count;

	count = 0;
	while (head != current)
	{
		if (get_token(head) == t)
			count++;
		head = head->next;
	}
	return (count);
}

void	n_free_leaks(t_lnode *p, t_lnode *current)
{
	t_lnode	*tmp;

	while (p != current)
	{
		tmp = p->next;
		free_lexer_node(p);
		p = tmp;
	}
}

void	norm_join_quote(t_lnode *current, t_lnode *node)
{
	if (get_token(current) == CMD)
	{
		set_cmd(node, ft_strjoin(get_cmd(node), get_cmd(current), 2));
		set_cmd(current, NULL);
	}
	else
		set_cmd(node, ft_strjoin(get_cmd(node),
				convert_token(get_token(current)), 0));
}
