#include "minishell.h"

void    ft_cd(t_parsing_node *root,t_exec_struct *exec_s)
{
    char *home_path;

    home_path = NULL;
    if (!(ft_strcmp(root->cmd.argv[0], "cd")) && root->cmd.argv[1] == NULL)
    {
        printf("here\n");
        home_path = get_env("HOME", exec_s, 0);
        chdir(home_path);
    }
}