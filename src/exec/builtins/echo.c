#include "minishell.h"

void    ft_echo(t_parsing_node *root)
{
    int i;
    int j;
    int ret;

    i = 2;
    j = 1;
    if (root->cmd.argv == NULL)
    {
        ret = write(1, "\n", 2);
        if (ret < 0)
            exit(-1);
    }
    else if (!(ft_strcmp(root->cmd.argv[1], "-n")))
    {
        while(root->cmd.argv[i])
        {
            if (root->cmd.argv[i + 1] == NULL)
                printf("%s", root->cmd.argv[i]);
            else
                printf("%s ", root->cmd.argv[i]);
            i++;
        }
    }
    else
    {
        while(root->cmd.argv[j])
        {
            if (root->cmd.argv[j + 1] == NULL)
                printf("%s", root->cmd.argv[j]);
            else
                printf("%s ", root->cmd.argv[j]);
            j++;
        }
        ret = write(1, "\n", 2);
        if (ret < 0)
            exit(-1);
    }
}