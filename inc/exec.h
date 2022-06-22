#ifndef EXEC_H
# define EXEC_H

typedef struct s_exec_struct
{
    /*environment variables*/
    char *path;

    
} t_exec_struct;

void execute(t_parsing_node *root, t_exec_struct *exec_s, char *envp[]);
void free_charpp(char **p);
char *get_env(char *var, char *envp[]);
char *check_if_bin_exist(char *bin_name, char *path_env);
int show_errno();

# endif