#include "minishell.h"

int it_contain_only(char *p, char c)
{
    int i;

    i = 0;
    while (p[i])
    {
        if (p[i] != c)
            return 0;
        i++;
    }
    return 1;
}

void    ft_echo(t_parsing_node *root)
{
    int i;
    int j;
    int ret;
    int flag;

    i = 2;
    j = 1;
    flag = 1;
    if (root->cmd.argv[1] == NULL)
    {
        ret = write(1, "\n", 2);
        if (ret < 0)
            exit(-1);
    }
    else if (!(ft_strcmp(root->cmd.argv[1], "-n")))
    {
        while(root->cmd.argv[i])
        {
            while (flag)
            {
                if (root->cmd.argv[i] && root->cmd.argv[i][0] == '-' && it_contain_only(&root->cmd.argv[i][1], 'n'))
                    i++;
                else
                    flag = 0;
            }
            if (root->cmd.argv[i] != NULL)
                if (root->cmd.argv[i + 1] == NULL)
                    printf("%s", root->cmd.argv[i]);
                else
                    printf("%s ", root->cmd.argv[i]);
            else
                break;
            i++;
        }
    }
    else
    {
        while (root->cmd.argv[j])
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
    exit_status_success();
}