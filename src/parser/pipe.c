#include "minishell.h"

t_lnode * find_pipe(t_lnode *head)
{
    t_lnode *current;

    current = head;
    while (current)
    {
        if (current->type.token == PIPE)
            return(current);
        current = current->next;
    }
    return (NULL);
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

t_parsing_node *pack_in_node(t_lnode** head)
{
    t_parsing_node *node;
    t_lnode* current;
    int i;

    ignore_spaces(head);
    node = alloc_node(CMD);
    node->cmd.cmd = ft_strdup(get_cmd(*head));
    current = (*head)->next;
    node->cmd.argv = (char **)malloc(sizeof(char *) * (cmd_count(current) + 1));
    if (node->cmd.argv == NULL)
        exit(-1);
    i = 0;
    while (current)
    {
        if (current->type.token == PIPE || current->type.token == EOL)
            return (node);
        else if (current->type.token == CMD)
            node->cmd.argv[i++] = ft_strdup(current->type.cmd);
        current = current->next;
    }
    node->cmd.argv[i] = NULL;
    return (NULL);
}

void handle_pipe(t_lnode** head)
{
    t_parsing_node *node;
    t_parsing_node *left;
    t_parsing_node *right;

    if (!find_pipe(*head))
        return;
    node = alloc_node(PIPE);
    left = pack_in_node(head);
    right = pack_in_node(&find_pipe(*head)->next);
    printf("Im here\n");

    add_left(node, left);
    add_right(node, right);
    inorder_show(node);

}