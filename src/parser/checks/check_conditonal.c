#include "minishell.h"

t_lnode *return_pipe_addr(t_lnode    *head)
{
    t_lnode *current;

    current = head;
    while(current)
    {
        if (get_token(current) == PIPE)
            return(current);
        else
            current = current->next;
    }
    return(NULL);
}

// Errror cases:
// 1 - A pipe with no CMD before and after (right and left)

int check_left_right(t_lnode* pipe, t_lnode *head)
{
    int check_left;
    int check_right;

    check_left = 0;
    while (head != pipe)
    {
        if (get_token(head) == CMD)
        {
            check_left = 1;
            break;
        }
        head = head->next;
    }

    head = pipe->next;
    check_right = 0;
    while (get_token(head) != PIPE && get_token(head) != EOL)
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


int check_pipe_syntax_errors(t_lnode* head)
{
    t_lnode *pipe;

    while (1)
    {
        pipe = return_pipe_addr(head);
        if (pipe == NULL)
            break;
        if (check_left_right(pipe, head) == 0)
        {
            printf("PIPE parse error!\n");
            return FAIL;
        }
        head = pipe->next;
    }

    return SUCCESS;
}