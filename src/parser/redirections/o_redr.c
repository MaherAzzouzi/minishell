/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_redr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:49:07 by snagat            #+#    #+#             */
/*   Updated: 2022/06/14 13:18:59 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// <
t_lnode *find_red(t_lnode *head, e_token redr)
{
    t_lnode *current;

    current = head;

    while (current)
    {
        if (get_token(current) == redr)
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
    
    last_token = EOL;
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

int fill_command_with_ore_args(t_lnode *cmd, t_lnode *head, char **argv)
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
            argv[counter++] = ft_strdup(get_cmd(head));
        head = head->next;
    }
    argv[counter] = NULL;
    return (counter);
}

int count_redirections(t_lnode *head, e_token redr)
{
    t_lnode *current;
    int count;

    count = 0;
    current = head;
    while (get_token(current) != EOL)
    {
        if (get_token(current) == redr)
            count++;
        current = current->next;
    }
    return count;
}


char **alloc_redr_array(t_lnode *head, e_token redr)
{
    int count;
    int i;
    char **redri_array;

    count = count_redirections(head, redr);
    redri_array = (char **)malloc((count + 1) * sizeof(char *));
    i = 0;
    if (!redri_array)
        exit(0);
    while (get_token(head) != EOL)
    {
        if (get_token(head) == redr)
        {
            head = head->next;
            while (get_token(head) == SPACE)
                head = head->next;
            if (get_token(head) == SGLQT || get_token(head) == DBLQT)
                head = head->next;
            redri_array[i++] = ft_strdup(get_cmd(head));
        }
        head = head->next;
    }
    redri_array[i] = NULL;
    return redri_array;
}

t_parsing_node *parse_redirections(t_lnode *head)
{
    t_parsing_node  *node;
    t_lnode         *cmd;
    int             count;
    
    if (find_red(head, REDRI) == NULL && find_red(head, REDRO) == NULL)
        return NULL;
    node = alloc_node(CMD);
    cmd = get_command(head);
    if (cmd)
    {
        node->cmd.cmd = get_cmd(cmd);
        count  = count_command_with_ore_args(cmd, head);
        node->cmd.argv = (char **)malloc(sizeof(char *) * (count + 1));
        if (node->cmd.argv == NULL)
            exit(-1);
        fill_command_with_ore_args(cmd, head, node->cmd.argv);
    }
    node->reds.i_r_params = alloc_redr_array(head, REDRI);
    node->reds.o_r_params = alloc_redr_array(head, REDRO);
    show_node(node);
    return node;
}