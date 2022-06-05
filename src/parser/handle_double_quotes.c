
#include "parser.h"
#include "minishell.h"
#include "lexer.h"

void clean_empty_quote(t_lnode **head, e_token t)
{
    t_lnode *current;
    t_lnode *p;
    int head_changed;

    current = *head;
    p = current;
    head_changed = 0;
    while (current)
    {
        while  (get_token(current) == t
            && current->next && is_empty(get_cmd(current->next))
            && current->next->next && (get_token(current->next->next) == t))
        {
            if (current == *head)
            {
                *head = current->next->next->next;
                head_changed = 1;
            }
            else
                p->next = current->next->next->next;
            free_lexer_node(current->next->next);
            free_lexer_node(current->next);
            free_lexer_node(current);
            if (head_changed)
                current = (*head);
            else
                current = p->next;
            head_changed = 0;
        }
        p = current;
        current = current->next;
    }
}

// We will get aa string like this ccc$HOME and expand it in the execution
int handle_double_quote(t_lnode	**head)
{
    handle_quote(*head, DBLQT);
	join_quotes(*head, DBLQT);
    clean_empty_quote(head, DBLQT);
    return(ft_check_quotes(*head, DBLQT));
}