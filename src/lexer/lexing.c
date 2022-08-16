/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:07:37 by mazzouzi          #+#    #+#             */
/*   Updated: 2022/06/08 18:43:12 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

e_token lexer_get_type(char a, char b)
{
	if (a == '\'')
		return (SGLQT);
	else if (a == '"')
		return (DBLQT);
	else if (a == '>')
		if (b == '>')
			return (APPND);
		else
			return (REDRO);
	else if (a == '<')
		if (b == '<')
			return (DLMI);
		else
			return (REDRI);
	else if (a == '|')
		if (b == '|')
			return (OR);
		else
			return (PIPE);
	else if (a == '&' && b == '&')
		return (AND);
	else if (a == '$')
		return (DLR);
	else if (a == '\0')
		return (EOL);
	else if (a == ' ')
		return (SPC);
	else if (a == '(')
		return (LEFT_PAR);
	else if (a == ')')
		return (RIGHT_PAR);
	else
		return (CMD);
}

t_lnode	*	ft_lexer(char *str)
{
	t_lnode	*head;
	e_token token;
	size_t i;
	int flag;

	i = 0;
	head = NULL;
	while (str[i])
	{
		flag = 0;
		token = lexer_get_type(str[i], str[i + 1]);
		ft_add_back_lex(&head, token, &str[i]);
		while (lexer_get_type(str[i], str[i + 1]) == CMD)
		{
			flag = 1;
			i++;
		}
		if (token == APPND || token == DLMI || token == OR || token == AND)
			i++;
		if (flag == 0)
			i++;
	}

	// This is called when str[i] is NULL.
	ft_add_back_lex(&head, EOL, NULL);
	return (head);
}

t_lnode *lex(char *cmd)
{
	t_lnode *head;

	head = ft_lexer(cmd);
	ignore_spaces(&head);
	return (head);
}