#include "minishell.h"

t_lnode *find_pipe(t_lnode **head)
{

    while (*head)
    {
        if ((*head)->type.token == PIPE)
            return(*head);
        (*head) = (*head)->next;
    }
    return (NULL);
}

int check_pipe(t_lnode  *head)
{
    t_lnode *current;

    current = head;
    while(current)
    {
        if (get_token(current) == PIPE)
            return(FOUND);
        current = current->next;
    }
    return(NOT_FOUND);
}

int cmd_count(t_lnode *head)
{
    t_lnode *current;
    int     i;

    current = head;
    i = 0;
    while(current)
    {
        if (current->type.token == PIPE || current->type.token == EOL)
            return(i);

        if (current->type.token == CMD)
            i++;
        current = current->next;
    }
    return (0);
}

t_parsing_node *pack_in_node(t_lnode* head)
{
    t_parsing_node *node;
    t_lnode* current;
    int i;

    while (get_token(head) != CMD)
        head = head->next;
    node = alloc_node(CMD);
    ///printf("CMD is %s\n", get_cmd(head));
    node->cmd.cmd = ft_strdup(get_cmd(head));
    current = (head)->next;
    node->cmd.argv = (char **)malloc(sizeof(char *) * (cmd_count(current) + 1));
    if (node->cmd.argv == NULL)
        exit(-1);
    i = 0;
    while (current)
    {
        if (current->type.token == PIPE || current->type.token == EOL)
        {
            node->cmd.argv[i] = NULL;
            return (node);
        }
        else if (current->type.token == CMD)
        {
            node->cmd.argv[i] = ft_strdup(current->type.cmd);
            i++;
        }
        current = current->next;
    }
    return (NULL);
}

t_parsing_node* handle_pipe_first(t_lnode** head)
{
    t_parsing_node *node;
    t_parsing_node *left;
    t_parsing_node *right;

    //if (!find_pipe(head))
    //    return NULL;
    node = alloc_node(PIPE);
    ignore_spaces(head);
    left = pack_in_node((*head));
    find_pipe(head);
    (*head) = (*head)->next;
    ignore_spaces(head);
    right = pack_in_node((*head));

    add_left(node, left);
    add_right(node, right);
    return node;
}

t_parsing_node* handle_pipe_next(t_lnode** head, t_parsing_node* left)
{
    t_parsing_node *node;
    t_parsing_node *right;

    //if (!find_pipe(head))
    //    return NULL;
    node = alloc_node(PIPE);
    find_pipe(head);
    (*head) = (*head)->next;
    ignore_spaces(head);
    right = pack_in_node((*head));

    add_right(node, right);
    add_left(node, left);
    return node;
}

void handle_pipe(t_lnode** head)
{
    t_parsing_node* node;
    node = NULL;

    if (check_pipe(*head))
        node = handle_pipe_first(head);
    while(check_pipe(*head))
        node = handle_pipe_next(head, node);    

    if (node)
        inorder_show(node);
}