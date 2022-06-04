
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
// char	*ft_strjoin(char const *s1, char const *s2)
void    handle_quotes(t_lnode *head)
{
    t_lnode *current;
    t_lnode *sg;
    t_lnode *node;
    t_lnode *p;
    char *sentence;

    current = head;
    while(current)
    {
        if (current->type.token == SGLQT)
        {
            node = (t_lnode *)malloc(sizeof(t_lnode));
            if (node == NULL)
                exit(1);
            node->type.cmd = malloc(1);
            node->type.token = CMD;
            sg = current;
            current = current->next;
            while (current->type.token != SGLQT)
            {
                if (current->type.token == CMD)
                    node->type.cmd = ft_strjoin(node->type.cmd, current->type.cmd, 2);
                else
                    node->type.cmd = ft_strjoin(node->type.cmd, convert_token(current->type.token), 0);
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
