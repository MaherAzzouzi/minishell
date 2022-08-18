// Convert between snagat's env linked list and mazzouzi's Array of pointers.

#include "minishell.h"

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
    if (!updated_envp)
        exit(-1);
    
    i = 0;
    current = env;
    while (i < len)
    {
        updated_envp[i] = ft_strdup(current->str);
        current = current->next;
        i++;
    }
    updated_envp[i] = NULL;
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