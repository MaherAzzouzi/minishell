#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_envp{
    char *str;
    struct s_envp *next;
} t_envp;
int  builtins(t_parsing_node *root, t_exec_struct *exec_s, t_envp *env);
void    ft_echo(t_parsing_node *root);
int    ft_cd(t_parsing_node *root,t_exec_struct *exec_s, t_envp *env);
int    ft_pwd(t_parsing_node *node, t_envp *env);
int ft_env(t_parsing_node *node, t_exec_struct *exec_s, t_envp *env);
t_envp	*ennv(t_exec_struct *exec);
void update_env(t_envp **en, char *str, char *path);
char *find_env(char *str, t_envp *env);
void    ft_exit(t_parsing_node *root,t_exec_struct *exec_s);
void	ft_unset(t_parsing_node *root, t_envp **env);
t_envp	*exxport(t_envp **envp);
void	ft_export(t_parsing_node *node, t_envp **env);

#endif