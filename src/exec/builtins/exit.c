#include "minishell.h"

void    ft_exit(t_parsing_node *root,t_exec_struct *exec_s)
{
    if (root->cmd.argv[0] != NULL && root->cmd.argv[1] == NULL)
    {
        exec_s->exit_status = ft_atoi(root->cmd.argv[0]);
        exit(exec_s->exit_status);
    }
    else if (root->cmd.argv[0] != NULL && root->cmd.argv[1] != NULL)
        ft_putstr_fd("exit: too many arguments", 2);
    else
        exit(exec_s->exit_status);
}