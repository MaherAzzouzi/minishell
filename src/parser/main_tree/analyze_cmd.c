#include "minishell.h"

int cmd_count(t_lnode *head, t_lnode *end)
{
    t_lnode *current;
    int     i;

    current = head;
    i = 0;
    while(current != end->next)
    {
        if (current == end)
            return(i);

        if (current->type.token == CMD)
            i++;
        current = current->next;
    }
    return (0);
}

t_parsing_node *pack_in_node(t_lnode *head, t_lnode *end)
{
    t_parsing_node *node;
    t_lnode* current;
    int i;

    node = alloc_node(CMD);
    head = ignore_spaces_ret(head);
    while (get_token(head) != SPACE && head != end)
    {
        printf("%s\n", convert_token(get_token(end)));
        if (get_token(head) == CMD)
        {
            node->cmd.cmd = ft_strjoin(node->cmd.cmd, get_cmd(head), 0);
        }
        head = head->next;
    }
    if (head == end)
    {
        return (node);
    }
    current = (head)->next;
    node->cmd.argv = (char **)malloc(sizeof(char *) * (cmd_count(current, end) + 1));
    if (node->cmd.argv == NULL)
        exit(-1);
    i = 0;
    while (current != end->next)
    {
        if (current == end)
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

t_parsing_node *analyze_return_node(t_lnode *start, t_lnode *end)
{
    t_parsing_node *node;

    node = NULL;
    node = parse_parenthesis(start, end);
    if (node == NULL)
    {
        node = parse_redirections(start, end);
        if (node == NULL)
        {
            node = pack_in_node(start, end);
        }
    }
    return(node);
}