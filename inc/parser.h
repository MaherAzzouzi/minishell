#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

struct s_command
{
    char **argv;
    char *cmd;
};

struct s_parsing_node
{
    e_token type;
    struct s_command cmd;
    struct s_parsing_node *lchild;
    struct s_parsing_node *rchild;
};

typedef struct s_parsing_node t_parsing_node;

t_parsing_node *alloc_node(e_token type);
t_parsing_node* go_left(t_parsing_node *node);
t_parsing_node* go_right(t_parsing_node *node);
void add_left(t_parsing_node *node, t_parsing_node *lnode);
void add_right(t_parsing_node *node, t_parsing_node *rnode);
void handle_pipe(t_lnode* head);
t_parsing_node *pack_in_node(t_lnode* head);
int cmd_count(t_lnode *head);
t_lnode * find_pipe(t_lnode *head);
void inorder_show(t_parsing_node *root);
void show_node(t_parsing_node *node);
void    handle_single_quote(t_lnode *head);
char    *convert_token(e_token  token);
void join_quotes(t_lnode *head);

# endif