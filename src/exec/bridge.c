// Convert between snagat's env linked list and mazzouzi's Array of pointers.

#include "minishell.h"

static void n_convert_p(char **updated_envp, int count)
{
    if (count == 0)
    {
        g_exec_struct->envp = updated_envp;
        count++;
    }
    else
    {
        free_charpp(g_exec_struct->envp);
        g_exec_struct->envp = updated_envp;
    }
}

void convert(t_envp *env)
{
    int len;
    t_envp *current;
    char **updated_envp;
    int i;
    static int count;

    len = 0;
    current = env;
    while (current != NULL)
    {
        len++;
        current = current->next;
    }
    updated_envp = (char **)malloc(sizeof(char *) * (len + 1));
    i = 0;
    current = env;
    while (i < len)
    {
        updated_envp[i] = ft_strdup(current->str);
        current = current->next;
        i++;
    }
    updated_envp[i] = NULL;
    n_convert_p(updated_envp, count);
}