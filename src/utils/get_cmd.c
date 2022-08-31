/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:46:26 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:47:02 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(t_lnode *node)
{
	return (node->type.cmd);
}

void	set_cmd(t_lnode *node, char *cmd)
{
	node->type.cmd = cmd;
}
