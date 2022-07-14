/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_redr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:49:07 by snagat            #+#    #+#             */
/*   Updated: 2022/06/15 14:20:00 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// <
t_lnode *find_red(t_lnode *head, t_lnode *end, e_token redr)
{
    t_lnode *current;

    current = head;
    while (current != end && current != NULL)
    {
        if (get_token(current) == redr)
            return (current);
        current = current->next;
    }
    return (NULL);
}

t_lnode *get_command(t_lnode *head, t_lnode *end)
{
    t_lnode *p;
    e_token last_token;

    p = head;
    
    last_token = EOL;
    head = ignore_spaces_ret(head);
    if (get_token(head) == CMD)
        return head;
    else if (get_token(head) == SGLQT || get_token(head) == DBLQT)
        return head->next;
    else
    {
        while (p != end)
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

int count_command_with_ore_args(t_lnode *cmd, t_lnode *head, t_lnode *end)
{
    int counter = 0;
    while (head != end)
    {
        if (head == cmd)
        {
            ;
        }
        else if (get_token(head) == REDRI || get_token(head) == REDRO
                || get_token(head) == DLMI || get_token(head) == APPND
                )
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
    return (counter);
}

int fill_command_with_ore_args(t_lnode *cmd, t_lnode *head, char **argv, t_lnode *end)
{
    int counter = 0;
    while (head != end)
    {
        if (head == cmd)
        {
            ;
        }
        else if (get_token(head) == REDRI || get_token(head) == REDRO
        || get_token(head) == DLMI || get_token(head) == APPND)
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

int count_redirections(t_lnode *head, e_token redr, t_lnode *end)
{
    t_lnode *current;
    int count;

    count = 0;
    current = head;
    while (current != end)
    {
        if (get_token(current) == redr)
            count++;
        current = current->next;
    }
    return (count);
}


char **alloc_redr_array(t_lnode *head, e_token redr, t_lnode *end)
{
    int count;
    int i;
    char **redri_array;

    count = count_redirections(head, redr, end);
    redri_array = (char **)malloc((count + 1) * sizeof(char *));
    i = 0;
    if (!redri_array)
        exit(0);
    while (head != end && head != NULL)
    {
        if (get_token(head) == redr)
        {
            head = head->next;
            while (get_token(head) == SPACE)
                head = head->next;
            if (get_token(head) == SGLQT || get_token(head) == DBLQT)
                head = head->next;
            if (get_token(head) != EOL)
                redri_array[i++] = ft_strdup(get_cmd(head));
        }
        head = head->next;
    }
    redri_array[i] = NULL;
    return redri_array;
}

t_parsing_node *parse_redirections(t_lnode *head, t_lnode *end)
{
    t_parsing_node  *node;
    t_lnode         *cmd;
    int             count;
    
    if (find_red(head, end, REDRI) == NULL && find_red(head, end, REDRO) == NULL
    && find_red(head, end, APPND) == NULL && find_red(head, end, DLMI) == NULL)
    {
        return NULL;
    }
    node = alloc_node(CMD);
    cmd = get_command(head, end);
    if (cmd)
    {
        free(node->cmd.cmd);
        node->cmd.cmd = ft_strdup(get_cmd(cmd));
        count  = count_command_with_ore_args(cmd, head, end);
        node->cmd.argv = (char **)malloc(sizeof(char *) * (count + 2));
        node->cmd.argv[0] = ft_strdup(get_cmd(cmd));
        if (node->cmd.argv == NULL)
            exit(-1);
        fill_command_with_ore_args(cmd, head, &node->cmd.argv[1], end);
    }
    node->reds.i_r_params = alloc_redr_array(head, REDRI, end);
    node->reds.o_r_params = alloc_redr_array(head, REDRO, end);
    node->reds.append_array = alloc_redr_array(head, APPND, end);
    node->reds.herdoc_array = alloc_redr_array(head, DLMI, end);
    return node;
}