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
int	check_empty_para(t_lnode *head);
int	check_if_balanced(t_lnode *head);
t_lnode	*return_lp(t_lnode *head);
int	check_left(t_lnode *head, t_lnode *lp);
int	get_env_variable_length(char *p);
char	*return_env(char *p);
char	*remove_char(char *p, char c);
char	*n_expand_an_array_having_dlr(char *result, char *env,
		char *q, t_exec_struct *exec_s);
char	*n_expand_an_array_having_dlr2(char *result, char *p);
char	*expand_an_array_having_dlr(char *p, t_exec_struct *exec_s);
char	*find_env_expand_1(char *result, char *env,
					char *q, t_exec_struct *exec_s);
char	*find_env_expand(t_lnode *node, t_exec_struct *exec_s);
t_lnode	*case_of_one_char_dollar(t_lnode **head, t_lnode *current,
		t_exec_struct *exec_s, int se);
void	combine_successive_cmds(t_lnode *head);
char	*case_of_one_char_dlr(char *p, t_exec_struct *exec_s);
void	n_expand_one_node(t_parsing_node *node,
		t_exec_struct *exec_s, char *p);
void	expand_one_node(t_parsing_node *node, t_exec_struct *exec_s);
t_lnode	*n_consolidate_dlr_with_cmd(t_lnode *current, t_lnode **head,
		int *is_current_changed);
t_lnode	*n_consolidate_dlr_with_cmd_2(t_lnode **head, t_exec_struct *exec_s,
			t_lnode *current, int *is_current_changed);
int	is_end_before_start(t_lnode *start, t_lnode *end);
t_lnode	*get_end(t_lnode *head);
t_lnode	*return_highest_priv(t_lnode *current, t_lnode *end);
t_lnode	*n_get_not_inside_p(t_lnode *current);
t_lnode	*stop_at_higher_priv(t_lnode *highest);
t_lnode	*find_next_right_par_or_eol(t_lnode *start);
char	*get_only_parenthesis_content(t_lnode *open_p, t_lnode *closing_p);
char	*cnvrt_tknv2(e_token token);
char	*convert_token(e_token token);
int	count_token(t_lnode *head, t_lnode *current, e_token t);
void	n_free_leaks(t_lnode *p, t_lnode *current);
void	norm_join_quote(t_lnode *current, t_lnode *node);
t_lnode	*handle_quote(t_lnode *head, e_token dlm);
t_lnode	*check_sglqt_dblqt(t_lnode *current, t_lnode *node);
void	free_quotes_leaks(t_lnode *temp, t_lnode *current);
void	join_quotes(t_lnode *head);
t_lnode	*handle_single_quote(t_lnode *head);

# endif