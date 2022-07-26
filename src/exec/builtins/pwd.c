#include "minishell.h"


void    ft_pwd(t_parsing_node *node)
{
    char *str;
    char cwd[1000];

    if (ft_strcmp(node->cmd.argv[0],"pwd") == 0 && node->cmd.argv[1] == 0)
    {
        str = getcwd(cwd, 1000);
        printf("%s\n", str);
    }
    else
        printf("invalid arguments\n");
}