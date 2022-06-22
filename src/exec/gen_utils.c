#include "minishell.h"

char **show_envp(char *envp[])
{
    int i;

    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
    return NULL;
}

void free_charpp(char **p)
{
    int i;

    i = 0;
    if (p)
    {
        while (p[i])
        {
            free(p[i]);
            i++;
        }
        free(p);
    }
}

char *get_env(char *var, char *envp[])
{
    int i;
    char **envpline;
    char *val;

    (void)var;
    i = 0;
    while (envp[i])
    {
        envpline = ft_split(envp[i], '=');
        if (ft_strncmp(envpline[0], var, ft_strlen(var)) == 0)
        {
            val = ft_strdup(envpline[1]);
            free_charpp(envpline);
            return val;
        }
        free_charpp(envpline);
        i++;
    }
    return (NULL);
}

char *check_if_bin_exist(char *bin_name, char *path_env)
{
    char **paths;
    char *full_path;
    int i;

    full_path = ft_strdup("");
    paths = ft_split(path_env, ':');
    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(full_path, paths[i], 0);
        full_path = ft_strjoin(full_path, "/", 0);
        full_path = ft_strjoin(full_path, bin_name, 0);
        if (access(full_path, X_OK) == 0)
        {
            return (full_path);
        }
        free(full_path);
        full_path = ft_strdup("");
        i++;
    }
    free_charpp(paths);
    return NULL;
}