#include "minishell.h"


static t_lnode* n_free_nodes(t_lnode **head, t_lnode *current, int *hc, t_lnode *p)
{
    free_lexer_node(current->next->next);
    free_lexer_node(current->next);
    free_lexer_node(current);
    if (*hc)
        current = (*head);
    else
        current = p->next;
    *hc = 0;
    return (current);
}
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
            current = n_free_nodes(head, current, &head_changed, p);
        }
        p = current;
        current = current->next;
    }
}

t_lnode* handle_double_quote(t_lnode	*head)
{
    return handle_quote(head, DBLQT);
} 