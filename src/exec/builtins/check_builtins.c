#include "minishell.h"

int    builtins(t_parsing_node *root, t_exec_struct *exec_s, t_envp * env)
{
    if (ft_strcmp("echo", root->cmd.cmd)==0)
    {
        ft_echo(root);
        return(1);
    }
    if (ft_strcmp("cd", root->cmd.cmd) == 0)
    {
        ft_cd(root, exec_s, env);
        return(1);
    }
    if (ft_strcmp("pwd", root->cmd.cmd) == 0)
    {
        ft_pwd(root, env);
        return 1;
    }
    if (ft_strcmp("env", root->cmd.cmd) == 0)
    {
        ft_env(root, exec_s, env);
        return(1);
    }
    return(0);
}