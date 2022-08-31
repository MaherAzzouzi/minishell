/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:53:40 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:58:07 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_command_line(t_exec_struct *exec_struct)
{
	char	*cmd;
	char	*cmd2;
	int		i;

	cmd = readline("$ ");
	if (!cmd)
	{
		if (g_exec_struct->exit_status == 256)
			exit(1);
		else
			exit(0);
	}
	add_history(cmd);
	i = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '\r'
		|| cmd[i] == '\n' || cmd[i] == '\f' || cmd[i] == '\v' )
		i++;
	cmd2 = ft_strdup(&cmd[i]);
	free(cmd);
	return (cmd2);
}

void	ctrl_c_handler(int p)
{
	(void)p;
	return ;
}

void	enter(int p)
{
	(void)p;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit_status_fail();
	return ;
}

void	loop_handler(char *envp[], t_exec_struct *exec_s)
{
	t_envp	*env;
	char	*cmd;

	env = ennv(exec_s);
	while (INFINIT)
	{
		cmd = read_command_line(exec_s);
		if (!cmd)
			exit(1);
		core(cmd, envp, exec_s, &env);
	}
}
