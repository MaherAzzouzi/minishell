
#include "parser.h"
#include "minishell.h"
#include "lexer.h"


int count_token(t_lnode* head, t_lnode *current, e_token t)
{
    int     count;

    count = 0;
    while (head != current)
    {
        if (get_token(head) == t)
            count++;
        head = head->next;
    }
    return (count);
}

char    *convert_token(e_token  token)
{
        if (token == SGLQT)
        return("'");
    else if (token == DBLQT)
        return("\"");
    else if (token == REDRI)
        return(">");
    else if (token == REDRO)
        return("<");
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

t_lnode*    handle_quote(t_lnode *head, e_token dlm)
{
    t_lnode *current;
    t_lnode *sg;
    t_lnode *node;
    t_lnode *p;

    current = head;
    node = ft_new_node_lex(CMD, "");
    sg = current;
    current = current->next;
    while (get_token(current) != dlm && get_token(current) != EOL)
    {
        if (get_token(current) == CMD)
            set_cmd(node, ft_strjoin(get_cmd(node), get_cmd(current), 2));
        else
            set_cmd(node, ft_strjoin(get_cmd(node), convert_token(get_token(current)), 0));
        p = current;
        current = current->next;
        free(p);
    }
    if (get_token(current) == EOL)
    {
        printf("Can not found a %s ender!\n", convert_token(dlm));
        return (t_lnode *)(-1);
    }
    sg->next = node;
    node->next = current;
    return current->next;
}

void join_quotes(t_lnode *head, e_token dlm)
{
    t_lnode *p;
    t_lnode *current;
    t_lnode *temp;
    t_lnode *node;
    t_lnode *tm;

    (void)dlm;
    current = head;
    while (current)
    {
        if ((get_token(current) == SGLQT || get_token(current) == DBLQT) && get_token(current->next) == CMD)
        {
            node = ft_new_node_lex(CMD, "");
            p = current;
            while ((get_token(current) == SGLQT || get_token(current) == DBLQT))
            {
                if (get_token(current->next) == CMD)
                {
                    set_cmd(node, ft_strjoin(get_cmd(node), get_cmd(current->next), 2));
                    current = current->next->next;
                }
                else if ((get_token(current) == SGLQT || get_token(current) == DBLQT) && (get_token(current->next) == DBLQT || get_token(current->next) == SGLQT))
                    current = current->next;
                else if ((get_token(current) == SGLQT || get_token(current) == DBLQT) && get_token(current->next) != CMD)
                    break;
                else if ((get_token(current) == SGLQT || get_token(current) == DBLQT))
                    current = current->next;
            }
            temp = p->next;
            while (temp != current)
            {
                tm = temp->next;
                free(temp);
                temp = tm;
            }
            p->next = node;
            node->next = current;
        }
        current = current->next;
    }
}

t_lnode *handle_single_quote(t_lnode	*head)
{
    //int ret;

    //ret = ft_check_siblings(*head, SGLQT);
    //if (ret == FAIL)
    //    return ret;
    return handle_quote(head, SGLQT);
	//join_quotes(*head, SGLQT);
    //clean_empty_quote(head, SGLQT);
    //return SUCCESS;
}
