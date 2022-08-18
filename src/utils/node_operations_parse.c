#include "parser.h"

t_parsing_node *alloc_node(e_token type)
{
    t_parsing_node *p;

    p = (t_parsing_node *)malloc(sizeof(t_parsing_node));
    if (!p)
        exit(-1);
    p->type = type;
    p->lchild = NULL;
    p->rchild = NULL;
    p->cmd.argv = NULL;
    p->cmd.cmd = ft_strdup("");
    p->reds.i_r_params = NULL;
    p->reds.o_r_params = NULL;
    p->reds.append_array = NULL;
    p->reds.herdoc_array = NULL;

    p->p.cmd = NULL;
    p->p.parenthesised = 0;
    return (p);
}

t_parsing_node* go_left(t_parsing_node *node)
{
    return (node->lchild);
}

t_parsing_node* go_right(t_parsing_node *node)
{
    return (node->rchild);
}

void add_left(t_parsing_node *node, t_parsing_node *lnode)
{
    node->lchild = lnode;
}

void add_right(t_parsing_node *node, t_parsing_node *rnode)
{
    node->rchild = rnode;
}

void ignore_spaces(t_lnode **head)
{
    t_lnode *current;

    while (get_token(*head) == SPC)
    {
        current = *(head);
        *head = (*head)->next;
        free(current);
    }
}

t_lnode *ignore_spaces_ret(t_lnode *head)
{
    while (get_token(head) == SPC)
        head = head->next;
    return head;
}