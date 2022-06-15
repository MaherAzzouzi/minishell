#include "minishell.h"
//#include "parser.h"

t_lnode *get_end(t_lnode *head)
{
    while (get_token(head) != EOL)
        head = head->next;
    return head;
}

t_lnode *return_highest_priv(t_lnode *start, t_lnode *end)
{
    t_lnode *current;
    t_lnode *p;
    int flag;

    p = get_end(start);
    flag = 0;
    current = start;
    while (current != end && get_token(current) != EOL)
    {
        if (get_token(current) == PIPE && flag == 0)
        {
            p = current;
            flag = 1;
        }
        else if (get_token(current) == AND || get_token(current) == OR)
        {
            p = current;
            return p;
        }
        current = current->next;
    }
    return (p);
}


t_parsing_node *recursive_tree_creation(t_lnode *start, t_lnode *end, t_lnode *prev_highest)
{
    t_parsing_node *node;
    t_lnode *highest;

    // Problem fixed do not change anything!
    // We just have to return node.
    highest = return_highest_priv(start, end);
    if (get_token(highest) != EOL)
        node = alloc_node(get_token(highest));
    if (get_token(highest) != PIPE && get_token(highest) != AND && get_token(highest) != OR)
    {
        //node = alloc_node(CMD);
        node = analyze_return_node(start, end);
        return node;
    }
    node->lchild = recursive_tree_creation(start, highest, highest);
    node->rchild = recursive_tree_creation(highest->next, prev_highest, highest);
    return node;
}

t_parsing_node *parse_tree(t_lnode *head)
{
    t_parsing_node * root = recursive_tree_creation(head, get_end(head), get_end(head));
    printf("--------------------\n");
    // inorder_show(root);
    print2D(root);
    return NULL;
}