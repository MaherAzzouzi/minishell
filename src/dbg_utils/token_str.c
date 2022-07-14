/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:48:09 by snagat            #+#    #+#             */
/*   Updated: 2022/06/08 18:44:39 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"


char    *enum_to_str(e_token   token)
{
    if (token == SGLQT)
        return("single quote");
    else if (token == DBLQT)
        return("double quotes");
    else if (token == REDRI)
        return("redirect input");
    else if (token == REDRO)
        return("redirect output");
    else if (token == DLMI)
        return ("delimiter");
    else if (token == APPND)
        return ("append");
    else if (token == PIPE)
        return ("PIPE");
    else if (token == CMD)
        return("cmd");
    else if (token == EOL)
        return("end of line");
    else if (token == SPC)
        return("space");
    else if (token == AND)
        return ("and");
    else if (token == OR)
        return ("or");
    else if (token == DLR)
        return ("dollar");
    else if (token == LEFT_PAR)
        return ("left paranthesis");
    else if (token == RIGHT_PAR)
        return ("right paranthesis");
    return(NULL);
}