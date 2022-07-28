#include "minishell.h"


int    ft_pwd(t_parsing_node *node)
{
    char *str;
    char cwd[1000];

    if (ft_strcmp(node->cmd.argv[0],"pwd") == 0 && node->cmd.argv[1] == 0)
    {
        str = getcwd(cwd, 1000);
        if (errno == ENOENT || str == NULL)
            perror("error\n");
        printf("%s\n", str);
        return(SUCCESS);
    }
    else
    {
        printf("invalid arguments\n");
        return(FAIL);
    }
        
}