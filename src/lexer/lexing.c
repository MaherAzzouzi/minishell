/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:07:37 by mazzouzi          #+#    #+#             */
/*   Updated: 2022/06/01 16:07:40 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
			return (REDRI);
	else if (a == '<')
		if (b == '<')
			return (DLMI);
		else
			return (REDRO);
	else if (a == '|')
		return (PIPE);
	else if (a == '$')
		return (DLR);
	else if (a == '\0')
		return (EOL);
	else if (a == ' ')
		return (SPACE);
	else
		return (CMD);
}

void	ft_lexer(char *str)
{
	t_lnode	*head;
	e_token token;
	size_t i;
	int flag;

	printf("Lexing %s\n", str);
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
		if (flag == 0)
			i++;
	}

	// This is called when str[i] is NULL.
	ft_add_back_lex(&head, EOL, NULL);
}
