#ifndef EXEC_H
# define EXEC_H

typedef struct s_exec_struct
{
    /*Environment variables*/
    char *path;
    char **envp;

    /*The last exit status will e stored here.*/
    int exit_status;
} t_exec_struct;

void execute(t_parsing_node *root, t_exec_struct *exec_s, char *envp[]);
void free_charpp(char **p);
char *get_env(char *var, char *envp[]);
char *check_if_bin_exist(char *bin_name, char *path_env);

char **show_envp(char *envp[]);
void init(t_exec_struct *exec_s, char *envp[]);
int show_errno();

int is_input_redirected(t_parsing_node *node);
int is_output_redirected(t_parsing_node *node);
int is_heredoc(t_parsing_node *node);
int is_append(t_parsing_node *node);
int handle_output_redirect(t_parsing_node *node);
int handle_herdoc(t_parsing_node *node);
int handle_append(t_parsing_node *node);
int handle_append_oredr(t_parsing_node *node);
int handle_herdoc_iredr(t_parsing_node *node);

# endif