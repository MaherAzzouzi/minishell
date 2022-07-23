/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:26:39 by snagat            #+#    #+#             */
/*   Updated: 2022/06/20 16:20:45 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"

int core(char *envp[])
{
	char *cmd;
	t_lnode	*head;
	t_parsing_node *root;
	t_exec_struct exec_struct;

	ft_memset(&exec_struct, 0, sizeof(exec_struct));

	setbuf(stdout, NULL);
	init(&exec_struct, envp);
	while (INFINIT)
	{
		cmd = readline("$PWNAI> ");
		add_history(cmd);
		head = lex(cmd);
		root = parse(&head, &exec_struct);
		if (root)
			execute(root, &exec_struct, envp);
		free_all(cmd, head, root);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	core(envp);
}
