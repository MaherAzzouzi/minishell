/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_redr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:49:07 by snagat            #+#    #+#             */
/*   Updated: 2022/06/13 18:50:33 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// <
t_lnode *find_o_red(t_lnode *head)
{
    t_lnode *current;

    current = head;

    while (current)
    {
        if (get_token(current) == REDRO)
            return (current);
        current = current->next;
    }
    return (NULL);
}

// >
t_lnode *find_i_red(t_lnode *head)
{
    t_lnode *current;

    current = head;

    while (current)
    {
        if (get_token(current) == REDRI)
            return (current);
        current = current->next;
    }
    return (NULL);
}

t_lnode *get_command(t_lnode *head)
{
    t_lnode *p;
    e_token last_token;

    p = head;
    
    if (get_token(head) == CMD)
        return head;
    else if (get_token(head) == SGLQT || get_token(head) == DBLQT)
        return head->next;
    else
    {
        while (get_token(p) != EOL)
        {
            if (get_token(p) == CMD && last_token == CMD)
                return(p);
            if (get_token(p) != SPACE && get_token(p) != SGLQT && get_token(p) != DBLQT)
                last_token = get_token(p);
            p = p->next;
        }
    }
    return (NULL);
}

int count_command_with_ore_args(t_lnode *cmd, t_lnode *head)
{
    int counter = 0;
    while (get_token(head) != EOL)
    {
        if (head == cmd)
        {
            ;
        }
        else if (get_token(head) == REDRI || get_token(head) == REDRO)
        {
            // should check for errors here instead
            printf("Token!\n");
            head = head->next;
            head = ignore_spaces_ret(head);
            if (get_token(head) == SGLQT || get_token(head) == DBLQT)
                head = head->next;
            if (get_token(head) != CMD)
            {
                printf("type %s\n", convert_token(get_token(head)));
                printf("[count_command_with_ore_args] Parse error!\n");
                exit(0);
            }
        } else if (get_token(head) == CMD)
            ++counter;
        head = head->next;
    }
    printf("Counter of argv is %d\n", counter);
    return (counter);
}

t_parsing_node *parse_redirections(t_lnode *head)
{
    t_parsing_node  *node;
    t_lnode         *cmd;
    
    if (find_i_red(head) == NULL && find_o_red(head) == NULL)
        return NULL;
    printf("Here\n");
    node = alloc_node(CMD);
    cmd = get_command(head);
    if (cmd)
    {
        printf("cmd is %s\n", get_cmd(cmd));
        count_command_with_ore_args(cmd, head);
    }
    return node;
    /*
    if (find_o_red(head) != NULL)
    {
        parse_output_redirection(head);
    }
    */
}