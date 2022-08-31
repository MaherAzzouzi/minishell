/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reds_exec_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:35:55 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:39:57 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_input_redirected(t_parsing_node *node)
{
	if (node->reds.i_r_params && node->reds.i_r_params[0])
		return (1);
	return (0);
}

int	is_output_redirected(t_parsing_node *node)
{
	if (node->reds.o_r_params && node->reds.o_r_params[0])
		return (1);
	return (0);
}

int	it_has_herdoc(t_parsing_node *node)
{
	if (node->reds.herdoc_array && node->reds.herdoc_array[0])
		return (1);
	return (0);
}

int	it_has_append(t_parsing_node *node)
{
	if (node->reds.append_array && node->reds.append_array[0])
		return (1);
	return (0);
}

int	handle_output_redirect(t_parsing_node *node)
{
	int	i;
	int	fd;

	if (!is_output_redirected(node))
		return (-1);
	i = 0;
	while (node->reds.o_r_params[i] && node->reds.o_r_params[i + 1] != NULL)
	{
		fd = open(node->reds.o_r_params[i], O_CREAT, 0664);
		if (fd < 0)
			exit(-1);
		i++;
	}
	fd = open(node->reds.o_r_params[i], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd < 0)
		exit(-1);
	return (fd);
}
