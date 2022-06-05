/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 13:16:36 by snagat            #+#    #+#             */
/*   Updated: 2022/06/05 13:46:58 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "lexer.h"


void    free_list(t_lnode **head)
{
    t_lnode *current;
    t_lnode *tmp;

    current = *head;
    if (*head == 0 || head == 0)
        return ;
    while(current)
    {
        tmp = current;
        free(tmp->type.cmd);
        current = current->next;
        free(tmp);
    }
    *head = 0;
}