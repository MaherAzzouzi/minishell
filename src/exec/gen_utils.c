#include "minishell.h"

char **show_envp(char *envp[])
{
    int i;

    i = 0;
    while (envp[i])
    {
        //printf("%s\n", envp[i]);
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

void reverse(char *p)
{
    int i;
    int j;
    char t;

    i = 0;
    j = strlen(p) - 1;

    while (i < j)
    {
        t = p[i];
        p[i] = p[j];
        p[j]= t;
        i++;
        j--;
    }
}

char *itoa(int d)
{
    char p[0x10];
    int i;
    int sign;

    ft_memset(p, 0, 0x10);
    i = 0;

    if (d == 0)
        p[0] = '0';
    else
    {
        if (d < 0)
        {
            sign = -1;
            d = -d;
        }
        while (d > 0)
        {
            p[i++] = (d % 10) + '0';
            d /= 10;
        }
        if (sign == -1)
            p[i] = '-';
        
        reverse(p);
    }
    return ft_strdup(p);
}

// `flag` will be used as envp just at the very first
char *get_env(char *var, void* exec_s, int flag)
{
    int i;
    char **envpline;
    char *val;
    char **envp;

    if (flag == 0)
        envp = ((t_exec_struct*)exec_s)->envp;
    else
        envp = (char**)exec_s;

    if (ft_strcmp(var, "$") == 0)
    {
        return itoa(getpid());
    }
    else if (ft_strcmp(var, "?") == 0)
    {
        return itoa(WEXITSTATUS(((t_exec_struct*)exec_s)->exit_status));
    }
    i= 0;
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
    return ft_strdup("");
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
    free(full_path);
    return NULL;
}


void init(t_exec_struct *exec_s, char *envp[])
{
    if (exec_s->path == NULL)
        exec_s->path = get_env("PATH", envp, 1);

    if (exec_s->envp == NULL)
        exec_s->envp = envp;
    
    exec_s->exit_status = 0;
}