/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:00:22 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 22:48:12 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parsing_node	*recursive_tree_creation(t_lnode *start, t_lnode *end)
{
	t_parsing_node	*node;
	t_lnode			*highest;

	node = NULL;
	highest = return_highest_priv(start, end);
	if (get_token(highest) != EOL)
		node = alloc_node(get_token(highest));
	if (get_token(highest) != PIPE
		&& get_token(highest) != AND
		&& get_token(highest) != OR)
	{
		node = analyze_return_node(start, end);
		return (node);
	}
	node->lchild = recursive_tree_creation(start, highest);
	node->rchild = recursive_tree_creation(highest->next,
			stop_at_higher_priv(highest));
	return (node);
}

t_parsing_node	*parse_tree(t_lnode *head)
{
	t_parsing_node	*root;

	root = recursive_tree_creation(head, get_end(head));
	return (root);
}
