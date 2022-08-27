#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

// Struct for both redirections < and >

typedef struct s_exec_struct
{
    /*Environment variables*/
    char *path;
    char **envp;

    /*The last exit status will be stored here.*/
    int exit_status;
} t_exec_struct;

// We will handle herdoc a bit special here due to environment variables expansion thing..
struct herdoc_exp
{
    char    *herdoc_keyword;
    int     is_quoted;
};

struct s_redirections
{
    char                **o_r_params;
    char                **i_r_params;
    struct herdoc_exp   **herdoc_array;
    char                **append_array;
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
    // Those just in case of herdoc
    int fd[2];
    // In some cases we need to know is << or < is at the end of the command.
    e_token last_in_token;
    // In some cases we need to know is > or >> is at the end of the command.
    e_token last_out_token;
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
int check_left_par(t_lnode *head);

void expand_env_variables(t_lnode **head, t_exec_struct* exec_s);
void handle_wildcard(t_lnode *head);
char *expand_an_array_having_dlr(char *p, t_exec_struct* exec_s);
void expand_one_node(t_parsing_node *node, t_exec_struct* exec_s);
void consolidate_dlr_with_cmd(t_lnode **head, t_exec_struct* exec_s);
void  replace(char *p, char a, char b);
t_parsing_node *parse(t_lnode **head, t_exec_struct* s);


# endif