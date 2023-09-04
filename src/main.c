/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:50:39 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 21:06:13 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	core(char *cmd, char *envp[], t_exec_struct *exec_struct, t_envp **env)
{
	t_lnode			*head;
	t_parsing_node	*root;

	(void)envp;
	head = lex(cmd);
	root = parse(&head, exec_struct);
	if (root)
		execute(root, exec_struct, env);
	free_all(cmd, head, root);
	return (WEXITSTATUS(exec_struct->exit_status));
}

int	main(int argc, char *argv[], char *envp[])
{
	t_exec_struct	exec_struct;

	(void)argv;
	(void)argc;
	//u can comment this if u dont have readline installed
	// rl_catch_signals = 0;
	rl_outstream = stderr;
	signal(SIGINT, enter);
	signal(SIGQUIT, SIG_IGN);
	g_exec_struct = &exec_struct;
	ft_memset(&exec_struct, 0, sizeof(exec_struct));
	init(&exec_struct, envp);
	loop_handler(envp, &exec_struct);
}
