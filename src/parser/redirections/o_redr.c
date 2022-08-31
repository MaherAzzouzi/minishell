/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_redr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:12:16 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 22:48:12 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parsing_node	*parse_redirections(t_lnode *hd, t_lnode *end)
{
	t_parsing_node	*node;
	t_lnode			*cmd;
	int				count;

	if (find_red(hd, end, REDRI) == NULL && find_red(hd, end, REDRO) == NULL
		&& find_red(hd, end, APPND) == NULL && find_red(hd, end, DLMI) == NULL)
		return (NULL);
	node = alloc_node(CMD);
	cmd = get_command(hd, end);
	if (cmd)
	{
		free(node->cmd.cmd);
		node->cmd.cmd = ft_strdup(get_cmd(cmd));
		count = count_command_with_ore_args(cmd, hd, end);
		node->cmd.argv = (char **)malloc(sizeof(char *) * (count + 2));
		node->cmd.argv[0] = ft_strdup(get_cmd(cmd));
		fill_command_with_ore_args(cmd, hd, &node->cmd.argv[1], end);
	}
	node->reds.i_r_params = alloc_redr_array(hd, REDRI, end);
	node->reds.o_r_params = alloc_redr_array(hd, REDRO, end);
	node->reds.append_array = alloc_redr_array(hd, APPND, end);
	node->reds.herdoc_array = alloc_herdoc_array(hd, DLMI, end);
	node->last_out_token = get_last_output_red(hd);
	node->last_in_token = get_last_in_red(hd);
	return (node);
}
