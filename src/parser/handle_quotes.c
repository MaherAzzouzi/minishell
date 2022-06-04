
#include "minishell.h"
#include "lexer.h"

char    *convert_token(e_token  token)
{
        if (token == SGLQT)
        return("'");
    else if (token == DBLQT)
        return("\"");
    else if (token == REDRI)
        return("<");
    else if (token == REDRO)
        return(">");
    else if (token == DLMI)
        return ("<<");
    else if (token == APPND)
        return (">>");
    else if (token == PIPE)
        return ("|");
    else if (token == DLR)
        return("$");
    else if (token == SPACE)
        return(" ");
    return(NULL);
}

void    handle_single_quote(t_lnode *head)
{
    t_lnode *current;
    t_lnode *sg;
    t_lnode *node;
    t_lnode *p;

    current = head;
    while(current)
    {
        if (current->type.token == SGLQT)
        {
            node = (t_lnode *)malloc(sizeof(t_lnode));
            if (node == NULL)
                exit(1);
            set_cmd(node, ft_strdup(""));
            set_token(node, CMD);
            sg = current;
            current = current->next;
            while (get_token(current) != SGLQT && get_token(current) != EOL)
            {
                if (get_token(current) == CMD)
                    set_cmd(node, ft_strjoin(get_cmd(node), get_cmd(current), 2));
                else
                    set_cmd(node, ft_strjoin(get_cmd(node), convert_token(get_token(current)), 0));
                p = current;
                current = current->next;
                free(p);
            }
            sg->next = node;
            node->next = current;
        }
        current = current->next;
    }
}

void join_quotes(t_lnode *head)
{
    t_lnode *p;
    t_lnode *current;
    t_lnode *temp;
    t_lnode *node;

    current = head;
    while (current)
    {
        if (get_token(current) == SGLQT && get_token(current->next) == CMD)
        {
            node = ft_new_node_lex(CMD, "");
            p = current;
            while (get_token(current) == SGLQT && get_token(current->next) == CMD)
            {
                set_cmd(node, ft_strjoin(get_cmd(node), get_cmd(current->next), 2));
                current = current->next->next;
            }
            temp = p->next;
            while(temp != current)
            {
                free(temp);
                temp = temp->next;
            }
            p->next = node;
            node->next = current;
        }
        current = current->next;
    }
}
