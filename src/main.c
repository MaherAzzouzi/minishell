/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:26:39 by snagat            #+#    #+#             */
/*   Updated: 2022/06/14 13:20:14 by snagat           ###   ########.fr       */
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


int order_quotes(t_lnode **head)
{
	t_lnode * current;

	current = *head;
	while (current)
	{
		if (get_token(current) == SGLQT)
		{
			current = handle_single_quote(current);
			if (current == (t_lnode *)-1)
				return FAIL;

		}
		else if (get_token(current) == DBLQT)
		{
			current = handle_double_quote(current);
			if (current == (t_lnode *)-1)
				return FAIL;
		} else
			current = current->next;
	}
	// join_quotes(*head);
	// join_cmd_with_quotes(head);
	return SUCCESS;
}

int core(int ac, char **av, char **envp)
{
	char *cmd;
	t_lnode	*head;
	(void)ac;
	(void)av;
	(void)envp;

	setbuf(stdout, NULL);
	while (INFINIT)
	{
		cmd = readline("$PWNAI> ");
		add_history(cmd);

		head = ft_lexer(cmd);
		ignore_spaces(&head);
		if (order_quotes(&head) == FAIL)
		{
			printf("PARSE ERROR\n");
			free_list(&head);
			free(cmd);
			continue;
		}
		log_(head);
		parse_tree(head);
		free_list(&head);
		free(cmd);
	}
}

int	main(int ac, char **av, char **envp)
{
	core(ac, av, envp);
}