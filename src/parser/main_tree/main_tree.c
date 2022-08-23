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

char **strdup_arrayp(char **p)
{
    int i;

    i = 0;
    if (!p)
        return NULL;
    while (p[i])
        i++;
    
    char **res = (char **)malloc(sizeof(char *) * (i + 1));
    if (!res)
        exit(-1);
    i = 0;
    while (p[i])
    {
        res[i] = ft_strdup(p[i]);
        i++;
    }
    res[i] = NULL;
    return res;
}

char **join_arrayp(char **a, char **b)
{
    char **res;
    int i;
    int size;

    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;
    else if (a == NULL && b == NULL)
        return NULL;

    size = 0;
    i = 0;
    while (a[i])
    {
        i++;
        size++;
    }
    i = 0;
    while (b[i])
    {
        i++;
        size++;
    }
    res = (char **)malloc(sizeof(char *) * (size + 1));
    i = 0;
    while (a[i])
    {
        res[i] = ft_strdup(a[i]);
        i++;
    }
    int j = 0;
    while (b[j])
    {
        res[i] = ft_strdup(b[j]);
        i++;
        j++;
    }
    res[i] = NULL;
    return res;
}

t_parsing_node* all_right(t_parsing_node* node)
{
    while (node->rchild != NULL)
        node = node->rchild;
    return (node);
}

void adjust_redirections(t_parsing_node* adjust, t_parsing_node* node)
{

    int flag;

    flag = 0;

    if (node->reds.append_array && adjust->reds.append_array &&
    node->reds.append_array[0] && adjust->reds.append_array[0])
    {
        adjust->reds.append_array = 
        join_arrayp(node->reds.append_array, adjust->reds.append_array);
        flag = 1;
    }
    else if (node->reds.append_array && node->reds.append_array[0])
    {
        adjust->reds.append_array = strdup_arrayp(node->reds.append_array);
        flag = 1;
    }
    
    if (node->reds.i_r_params && adjust->reds.i_r_params &&
    node->reds.i_r_params[0] && adjust->reds.i_r_params[0])
    {
        adjust->reds.i_r_params = 
        join_arrayp(node->reds.i_r_params, adjust->reds.i_r_params);
        flag = 1;
    }
    else if (node->reds.i_r_params && node->reds.i_r_params[0])
    {
        adjust->reds.i_r_params = strdup_arrayp(node->reds.i_r_params);
        flag  =1;
    }

    if (node->reds.o_r_params && adjust->reds.o_r_params &&
    node->reds.o_r_params[0] && adjust->reds.o_r_params[0])
    {
        adjust->reds.o_r_params = 
        join_arrayp(node->reds.o_r_params, adjust->reds.o_r_params);
        flag = 1;
    }
    else if (node->reds.o_r_params && node->reds.o_r_params[0])
    {
        adjust->reds.o_r_params = strdup_arrayp(node->reds.o_r_params);
        flag = 1;
    }
    if (flag)
    {
        adjust->last_in_token = node->last_in_token;
       adjust->last_out_token = node->last_out_token;
    }
}

int it_has_redirections(t_parsing_node *p)
{
    if (p->reds.append_array && p->reds.append_array[0])
        return 1;
    if (p->reds.i_r_params && p->reds.i_r_params[0])
        return 1;
    if (p->reds.o_r_params && p->reds.o_r_params[0])
        return 1;
    return 0;
}

// expand parenthesis into subtrees.
t_parsing_node *expand_node(t_parsing_node *node)
{
    int l;
    int r;
    t_parsing_node *p;
    t_parsing_node *adjust;

    l = 0;
    r = 0;
    if (node == NULL)
        return NULL;
    if (node && node->p.parenthesised == 1)
    {
        p = node;
        node = lex_and_parse(node->p.cmd);
        node->p.parenthesised = 1;
        if (it_has_redirections(p))
        {
            adjust = all_right(node);
            // If it already have redirections do not bother changing it.
            adjust_redirections(adjust, p);
        }
        free_node(p);
    }
    if (node->lchild && node->lchild->p.parenthesised == 1)
    {
        p = node->lchild;
        // need to free before just overwrite.
        node->lchild = lex_and_parse(node->lchild->p.cmd);
        node->lchild->p.parenthesised = 1;
        if (it_has_redirections(p))
        {
            adjust = all_right(node->lchild);
            // If it already have redirections do not bother changing it.
            adjust_redirections(adjust, p);
        }
        //show_node(node->lchild);
        l = 1;
        free_node(p);
    }
    if (node->rchild && node->rchild->p.parenthesised == 1)
    {
        p = node->rchild;
        node->rchild = lex_and_parse(node->rchild->p.cmd);
        node->rchild->p.parenthesised = 1;
        if (it_has_redirections(p))
        {
            adjust = all_right(node->rchild);
            // If it already have redirections do not bother changing it.
            adjust_redirections(adjust, p);
        }
        r = 1;
        free_node(p);
    }
    if (l == 0)
        node->lchild = expand_node(node->lchild);
    if (r == 0)
        node->rchild = expand_node(node->rchild);
    return node;
}

t_parsing_node *parse_tree(t_lnode *head)
{
    t_parsing_node * root = recursive_tree_creation(head, get_end(head));
    if (g_expand_node == 1)
    {
        root = expand_node(root);
    }
    return root;
}