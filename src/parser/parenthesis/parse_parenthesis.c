#include "minishell.h"

t_lnode *find_next_right_par_or_eol(t_lnode *start)
{
    while (1)
    {
        if (get_token(start) == RIGHT_PAR || get_token(start) == EOL || get_token(start) == AND || get_token(start) == OR || get_token(start) == PIPE)
            return start;
        start = start->next;
    }
    return NULL;
}

t_parsing_node *parse_parenthesis(t_lnode *head, t_lnode *end)
{
    t_lnode *current;
    int count;
    char *cmd;
    t_parsing_node *node;

    count = 0;
    current = head;
    cmd = ft_strdup("");
    node = alloc_node(CMD);
    while (current != end)
    {
        if (get_token(current) == LEFT_PAR)
        {
            current = current->next;
            while (current != end)
            {
                if (get_token(current) == LEFT_PAR)
                    count++;
                if (get_token(current) == RIGHT_PAR && count == 0)
                    break;
                else if (get_token(current) == RIGHT_PAR)
                    count--;
                if (get_token(current) == CMD)
                    cmd = ft_strjoin(cmd, get_cmd(current), 0);
                else
                    cmd = ft_strjoin(cmd, convert_token(get_token(current)), 0);
                current = current->next;
            }
            if (get_token(current) == RIGHT_PAR && count == 0)
                break;
        }
        current = current->next;
    }
    if (cmd[0] != 0)
    {
        t_parsing_node *n = parse_redirections(current->next, find_next_right_par_or_eol(current->next));
        if (n == NULL)
        {
            node->p.parenthesised = 1;
            node->p.cmd = cmd;
            // Before exiting we should look for redirections too.
            return (node);
        }
        else
        {
            free_node(node);
            n->p.cmd = cmd;
            n->p.parenthesised = 1;
            return n;
        }
    }
    else
    {
        free(cmd);
        free_node(node);
        return NULL;
    }
}