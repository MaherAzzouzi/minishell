/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:26:39 by snagat            #+#    #+#             */
/*   Updated: 2022/06/06 16:17:33 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>

void log_(t_lnode *head)
{
	printf("--------------------\n");
	ft_check_lists(head);
	printf("--------------------\n");
}

int core(int ac, char **av, char **envp)
{
	char *cmd;
	t_lnode	*head;
	(void)ac;
	(void)av;
	(void)envp;
	while (INFINIT)
	{
		cmd = readline("$PWNAI> ");
		add_history(cmd);

		head = ft_lexer(cmd);
		ignore_spaces(&head);

		if (handle_single_quote(&head) == FAIL)
			printf("Parse error!\n");
		if (handle_double_quote(&head) == FAIL)
			printf("Parse error!\n");
		log_(head);

		handle_pipe(&head);
		free_list(&head);
		free(cmd);
	}
}

int	main(int ac, char **av, char **envp)
{
	core(ac, av, envp);
}