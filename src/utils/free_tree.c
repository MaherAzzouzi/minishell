/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:43:41 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 22:55:49 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array_of_pointers(char **p)
{
	int	i;

	if (p)
	{
		i = 0;
		while (p[i])
		{
			free(p[i]);
			i++;
		}	
		free(p);
	}
}

void	free_herdocs(struct s_herdoc_exp **p)
{
	int	i;

	if (p)
	{
		i = 0;
		while (p[i])
		{
			free(p[i]->herdoc_keyword);
			free(p[i]);
			i++;
		}
		free(p);
	}
}

void	free_node(t_parsing_node *node)
{
	if (node->cmd.cmd)
		free(node->cmd.cmd);
	free_array_of_pointers(node->cmd.argv);
	free_array_of_pointers(node->reds.append_array);
	free_herdocs(node->reds.herdoc_array);
	free_array_of_pointers(node->reds.i_r_params);
	free_array_of_pointers(node->reds.o_r_params);
	if (node->p.cmd)
		free(node->p.cmd);
	free(node);
}

void	free_tree(t_parsing_node *root)
{
	if (root == NULL)
		return ;
	free_tree(root->lchild);
	free_tree(root->rchild);
	free_node(root);
}
