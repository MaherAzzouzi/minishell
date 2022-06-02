/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:48:09 by snagat            #+#    #+#             */
/*   Updated: 2022/06/02 10:12:58 by snagat           ###   ########.fr       */
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
    else if (token == DLR)
        return("$");
    else if (token == CMD)
        return("cmd");
    else if (token == EOL)
        return("end of line");
    else if (token == SPACE)
        return("space");
    return(NULL);
}