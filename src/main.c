/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:26:39 by snagat            #+#    #+#             */
/*   Updated: 2022/06/01 12:48:15 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include <readline/readline.h>
#include <readline/history.h>


int	main(int ac, char **av, char **envp)
{
	char *cmd;

	while (INFINIT)
	{
		cmd = readline(GREEN "$PWNAI> " WHITE);
		ft_lexer(cmd);
	}
}