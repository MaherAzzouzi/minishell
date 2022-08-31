/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:19:03 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:19:05 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_parsing_node *root, t_exec_struct *exec_s)
{
	(void)exec_s;
	if (root->cmd.argv[1] != NULL && root->cmd.argv[2] != NULL)
	{
		show_message("exit", "too many arguments");
		exit_status_fail();
	}
	else if (root->cmd.argv[0] != NULL && root->cmd.argv[1] != NULL)
		exit (ft_atoi(root->cmd.argv[1]));
	else
		exit (0);
}
