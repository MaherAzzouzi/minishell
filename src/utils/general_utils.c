/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:45:51 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:59:23 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty(char *p)
{
	return (p && p[0] == 0);
}

t_parsing_node	*go_left(t_parsing_node *node)
{
	return (node->lchild);
}

t_parsing_node	*go_right(t_parsing_node *node)
{
	return (node->rchild);
}

void	add_left(t_parsing_node *node, t_parsing_node *lnode)
{
	node->lchild = lnode;
}

void	add_right(t_parsing_node *node, t_parsing_node *rnode)
{
	node->rchild = rnode;
}
