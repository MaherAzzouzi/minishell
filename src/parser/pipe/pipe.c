// #include "minishell.h"

// t_lnode *find_pipe(t_lnode **head)
// {
//    // t_lnode *current;

//     while (*head)
//     {
//         if ((*head)->type.token == PIPE)
//             return(*head);
//         //current = (*head);
//         (*head) = (*head)->next;
//         //free(current);
//     }
//     return (NULL);
// }

// int check_pipe(t_lnode  *head)
// {
//     t_lnode *current;

//     current = head;
//     while(current)
//     {
//         if (get_token(current) == PIPE)
//             return(FOUND);
//         current = current->next;
//     }
//     return(NOT_FOUND);
// }

// int cmd_count(t_lnode *head)
// {
//     t_lnode *current;
//     int     i;

//     current = head;
//     i = 0;
//     while(current)
//     {
//         if (current->type.token == PIPE || current->type.token == EOL)
//             return(i);

//         if (current->type.token == CMD)
//             i++;
//         current = current->next;
//     }
//     return (0);
// }

// t_parsing_node *pack_in_node(t_lnode* head)
// {
//     t_parsing_node *node;
//     t_lnode* current;
//     int i;

//     node = alloc_node(CMD);
//     while (get_token(head) != SPACE && get_token(head) != PIPE && get_token(head) != EOL)
//     {
//         if (get_token(head) != CMD)
//             node->cmd.cmd = ft_strjoin(node->cmd.cmd, convert_token(get_token(head)), 0);
//         else
//         {
//             node->cmd.cmd = ft_strjoin(node->cmd.cmd, get_cmd(head), 0);
//         }
//         head = head->next;
//     }
//     if (get_token(head) == EOL || get_token(head) == PIPE)
//     {
//         return (node);
//     }
//     current = (head)->next;
//     node->cmd.argv = (char **)malloc(sizeof(char *) * (cmd_count(current) + 1));
//     if (node->cmd.argv == NULL)
//         exit(-1);
//     i = 0;
//     while (current)
//     {
//         if (current->type.token == PIPE || current->type.token == EOL)
//         {
//             node->cmd.argv[i] = NULL;
//             return (node);
//         }
//         else if (current->type.token == CMD)
//         {
//             node->cmd.argv[i] = ft_strdup(current->type.cmd);
//             i++;
//         }
//         current = current->next;
//     }
//     return (NULL);
// }

// t_parsing_node* handle_pipe_first(t_lnode** head)
// {
//     t_parsing_node *node;
//     t_parsing_node *left;
//     t_parsing_node *right;

//     //if (!find_pipe(head))
//     //    return NULL;
//     node = alloc_node(PIPE);
//     ignore_spaces(head);
//     left = pack_in_node((*head));
//     find_pipe(head);
//     (*head) = (*head)->next;
//     ignore_spaces(head);
//     right = pack_in_node((*head));

//     add_left(node, left);
//     add_right(node, right);
//     return node;
// }

// t_parsing_node* handle_pipe_next(t_lnode** head, t_parsing_node* left)
// {
//     t_parsing_node *node;
//     t_parsing_node *right;

//     //if (!find_pipe(head))
//     //    return NULL;
//     node = alloc_node(PIPE);
//     find_pipe(head);
//     (*head) = (*head)->next;
//     ignore_spaces(head);
//     right = pack_in_node((*head));

//     add_right(node, right);
//     add_left(node, left);
//     return node;
// }

// void handle_pipe(t_lnode* head)
// {
//     t_lnode *head_p[1];
//     t_parsing_node* node;
//     node = NULL;
    
//     *head_p = head;
//     if (check_pipe(*head_p))
//         node = handle_pipe_first(head_p);
//     while(check_pipe(*head_p))
//         node = handle_pipe_next(head_p, node);
//     if (node)
//         inorder_show(node);
    
//     free_tree(node);
// }