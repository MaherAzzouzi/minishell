#include "minishell.h"

void    builtins(t_parsing_node *root, t_exec_struct *exec_s)
{

    if (!(ft_strcmp("echo", root->cmd.cmd)))
            ft_echo(root);
    else if (!(ft_strcmp("cd", root->cmd.cmd)))
            ft_cd(root, exec_s);

}