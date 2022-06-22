#include "minishell.h"

void    builtins(t_parsing_node *root)
{

    if (!(ft_strcmp("echo", root->cmd.cmd)))
            ft_echo(root);

}