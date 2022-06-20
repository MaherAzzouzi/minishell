#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"


// Struct for both redirections < and >

struct s_redirections
{
    char    **o_r_params;
    char    **i_r_params;
    char    **herdoc_array;
    char    **append_array;
};

typedef struct s_redirections t_reds;

struct s_command
{
    char **argv;
    char *cmd;
};

typedef struct s_parat
{
    int parenthesised;
    char *cmd;
}t_parat;

struct s_parsing_node
{
    e_token type;
    t_parat p;
    struct s_command cmd;
    // In case we have redirections < and >.
    t_reds reds;
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
t_parsing_node *pack_in_node(t_lnode* head, t_lnode *end);
int cmd_count(t_lnode *head, t_lnode *end);
t_lnode * find_pipe(t_lnode **head);
void inorder_show(t_parsing_node *root);
void print2D(t_parsing_node *root);
void show_node(t_parsing_node *node);
t_lnode*    handle_quote(t_lnode *head, e_token t);
char    *convert_token(e_token  token);
void join_quotes(t_lnode *head);
void join_cmd_with_quotes(t_lnode **head);
t_lnode* handle_single_quote(t_lnode	*head);
t_lnode* handle_double_quote(t_lnode	*head);
void clean_empty_quote(t_lnode **head, e_token t);
int    ft_check_quotes(t_lnode *head, e_token dlm);
int	ft_check_siblings(t_lnode	*head, e_token dlm);
t_lnode *ignore_spaces_ret(t_lnode *head);


t_parsing_node *recursive_tree_creation(t_lnode *start, t_lnode *end);
t_parsing_node * parse_tree(t_lnode *head);
t_parsing_node *analyze_return_node(t_lnode *start, t_lnode *end);

// Parenthesis.
t_parsing_node *parse_parenthesis(t_lnode *head, t_lnode *end);


# endif