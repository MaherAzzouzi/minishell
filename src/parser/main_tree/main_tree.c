#include "minishell.h"
//#include "parser.h"

int is_end_before_start(t_lnode *start, t_lnode *end)
{
    while (end && get_token(end) != EOL)
    {
        if (end == start)
        {
            return 1;
        }
        end = end->next;
    }
    return 0;
}
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
    int count;
    
    p = get_end(start);
    flag = 0;
    current = start;
    count = 0;
    while (current != end && get_token(current) != EOL)
    {
        if (get_token(current) == LEFT_PAR)
            count++;
        if (get_token(current) == PIPE && flag == 0 && count == 0 && get_token(p) != OR && get_token(p) != AND)
        {
            p = current;
            flag = 1;
        }
        else if ((get_token(current) == AND || get_token(current) == OR)
                && count == 0)
        {
            p = current;
            //return p;
        }
        if (get_token(current) == RIGHT_PAR)
            count--;
        current = current->next;
    }
    return (p);
}

t_lnode *stop_at_higher_priv(t_lnode *highest)
{
    t_lnode *current;

    current = highest;

    if (get_token(highest) == PIPE)
    {
        while (get_token(current) != EOL)
        {
            if (get_token(current) == AND || get_token(current) == OR)
                return current;
            current = current->next;
        }
        return current;
    }
    else if (get_token(highest) == AND || get_token(highest) == OR)
    {
        int count = 0;
        current = current->next;
        while (get_token(current) != EOL)
        {
            if (get_token(current) == LEFT_PAR)
                count++;
            else if ((get_token(current) == AND || get_token(current) == OR) && count == 0)
                return current;
            else if (get_token(current) == RIGHT_PAR)
                count--;
            current = current->next;
        }
        return current;
    }
    else
        return (highest);
}

t_parsing_node *recursive_tree_creation(t_lnode *start, t_lnode *end)
{
    t_parsing_node *node;
    t_lnode *highest;

    node = NULL;
    highest = return_highest_priv(start, end);
    if (get_token(highest) != EOL)
        node = alloc_node(get_token(highest));
    if (get_token(highest) != PIPE && get_token(highest) != AND && get_token(highest) != OR)
    {
        node = analyze_return_node(start, end);
        return node;
    }
    node->lchild = recursive_tree_creation(start, highest);
    node->rchild = recursive_tree_creation(highest->next, stop_at_higher_priv(highest));
    return node;
}

t_parsing_node *lex_and_parse(char *cmd)
{
    t_lnode *head = lex(cmd);
    t_parsing_node* root = parse(&head, g_exec_struct);
    // printf("expand subtree\n");
    // print2D(root);
    // FIXME: Should free lex here and free parse later
    return root;
}

// expand parenthesis into subtrees.
t_parsing_node *expand_node(t_parsing_node *node)
{
    int l;
    int r;
    t_parsing_node *p;

    l = 0;
    r = 0;
    if (node == NULL)
        return NULL;
    if (node && node->p.parenthesised == 1)
    {
        p = node;
        node = lex_and_parse(node->p.cmd);
        node->p.parenthesised = 1;
        free_node(p);
        return node;
    }
    if (node->lchild && node->lchild->p.parenthesised == 1)
    {
        p = node->lchild;
        // need to free before just overwrite.
        node->lchild = lex_and_parse(node->lchild->p.cmd);
        node->lchild->p.parenthesised = 1;
        show_node(node->lchild);
        l = 1;
        free_node(p);
    }
    if (node->rchild && node->rchild->p.parenthesised == 1)
    {
        p = node->rchild;
        node->rchild = lex_and_parse(node->rchild->p.cmd);
        node->rchild->p.parenthesised = 1;
        r = 1;
        free_node(p);
    }
    if (l == 0)
        node->lchild = expand_node(node->lchild);
    if (r == 0)
    {
        node->rchild = expand_node(node->rchild);
    }
    return node;
}

t_parsing_node *parse_tree(t_lnode *head)
{
    t_parsing_node * root = recursive_tree_creation(head, get_end(head));
    if (g_expand_node == 1)
        root = expand_node(root);
    return root;
}