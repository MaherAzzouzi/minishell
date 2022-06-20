#include "minishell.h"

t_lnode *return_condt_addr(t_lnode    *head)
{
    t_lnode *current;

    current = head;
    while(current)
    {
        if (get_token(current) == PIPE 
            || get_token(current) == AND
            || get_token(current) == OR)
            return(current);
        else
            current = current->next;
    }
    return(NULL);
}

int check_left_right(t_lnode* condt, t_lnode *head)
{
    int check_left;
    int check_right;

    check_left = 0;
    while (head != condt)
    {
        if (get_token(head) == CMD)
        {
            check_left = 1;
            break;
        }
        head = head->next;
    }

    head = condt->next;
    check_right = 0;
    while ((get_token(head) != get_token(condt)) 
        && get_token(head) != EOL)
    {
        if (get_token(head) == CMD)
        {
            check_right = 1;
            break;
        }
        head = head->next;
    }
    return (check_left && check_right);
}

int check_condt_syntax_errors(t_lnode* head)
{
    t_lnode *condt;

    while (1)
    {
        condt = return_condt_addr(head);
        if (condt == NULL)
            break;
        if (check_left_right(condt, head) == 0)
            return FAIL;
        head = condt->next;
    }
    return SUCCESS;
}