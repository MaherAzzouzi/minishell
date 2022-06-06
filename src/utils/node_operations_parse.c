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
    p->cmd.cmd = NULL;
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
    while (get_token(*head) == SPACE)
        *head = (*head)->next;
}