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
	else
		return (CMD);

}

void	ft_lexer(char *str)
{
	size_t i;

	printf("Lexing %s\n", str);
	while (str[i])
	{
		lexer_get_type(str[i], str[i + 1]);
		i++;
	}

	// This is called when str[i] is NULL.
	lexer_get_type(str[i], str[i]);
}
