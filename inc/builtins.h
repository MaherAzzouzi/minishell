#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_envp{
    char *str;
    struct s_envp *next;
} t_envp;
int  builtins(t_parsing_node *root, t_exec_struct *exec_s, t_envp *env);
void    ft_echo(t_parsing_node *root);
int    ft_cd(t_parsing_node *root,t_exec_struct *exec_s, t_envp *env);
int    ft_pwd(t_parsing_node *node);
int ft_env(t_parsing_node *node, t_exec_struct *exec_s, t_envp *env);
t_envp	*ennv(t_exec_struct *exec);
void update_env(t_envp **en, char *str, char *path);

#endif