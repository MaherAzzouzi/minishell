/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:26:39 by snagat            #+#    #+#             */
/*   Updated: 2022/06/05 13:40:53 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>


int	main(int ac, char **av, char **envp)
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

		//handle_single_quote(head);
		handle_double_quote(&head);
		//handle_single_quote(head);

		printf("--------------------\n");
		ft_check_lists(head);
		printf("--------------------\n");

		//handle_pipe(head);
		free_list(&head);
		free(cmd);
	}
}