/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:33:49 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:52:08 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_exec_struct *exec_s, char *envp[])
{
	setbuf(stdout, NULL);
	if (exec_s->path == NULL)
		exec_s->path = get_env("PATH", envp, 1);
	if (exec_s->envp == NULL)
		exec_s->envp = envp;
	exec_s->exit_status = 0;
}
