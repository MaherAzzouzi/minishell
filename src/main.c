/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:26:39 by snagat            #+#    #+#             */
/*   Updated: 2022/06/08 18:38:18 by snagat           ###   ########.fr       */
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
	t_lnode *head2;
	(void)ac;
	(void)av;
	(void)envp;
	while (INFINIT)
	{
		cmd = readline("$PWNAI> ");
		add_history(cmd);

		head = ft_lexer(cmd);
		head2 = head;
		ignore_spaces(&head);

		if (handle_single_quote(&head) == FAIL)
			printf("Parse error!\n");
			
		if (handle_double_quote(&head) == FAIL)
			printf("Parse error!\n");
		log_(head);

		if (check_pipe_syntax_errors(head) == FAIL)
		{
			free_list(&head);
			free(cmd);
			continue;
		}
		handle_pipe(&head);
		free_list(&head2);
		free(cmd);
	}
}

int	main(int ac, char **av, char **envp)
{
	core(ac, av, envp);
}