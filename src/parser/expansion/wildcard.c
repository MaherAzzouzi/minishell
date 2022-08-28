#include "minishell.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>

#define TRUE 1
#define FALSE 0

int is_matching(char *str, char *pattern, int n, int m) {
    if (n == 0 && m == 0)
        return TRUE;
    int i;
    int j;

    int **lookup;

    lookup = (int **)malloc((n + 1) * sizeof(int*));
    memset(lookup, 0, (n + 1) * sizeof(int*));
    i = 0;
    while (i <= n)
    {
        lookup[i] = (int *)malloc((m + 1) * sizeof(int));
        memset(lookup[i], 0, (m + 1) * sizeof(int));
        i++;
    }
    lookup[0][0] = TRUE;
    j = 1;
    // in case the string is empty
    while (j <= m)
    {
        if (pattern[j - 1] == '*')
            lookup[0][j] = lookup[0][j-1];
        j++;
    }
    i = 1;
    while (i <= n)
    {
        j = 1;
        while (j <= m)
        {
            if (pattern[j - 1] == '*')
                lookup[i][j] = lookup[i-1][j] | lookup[i][j-1];
            else if (pattern[j - 1] == str[i - 1])
                lookup[i][j] = lookup[i-1][j-1];
            else
                lookup[i][j] = FALSE;
            j++;
        }
        i++;
    }
    int ret = lookup[n][m];
    i = 0;
    while (i <= n)
    {
        free(lookup[i]);
        i++;
    }
    free(lookup);
    return ret;
}

char    *open_current_dir(char *pattern)
{
    DIR *d;
    struct dirent *content;
    char *p;

    p = ft_strdup("");
    d = opendir(".");
    while (1)
    {
        content = readdir(d);
        if (content == NULL)
            break;
        if (content->d_name[0] != '.' &&
        is_matching(content->d_name, pattern, ft_strlen(content->d_name), ft_strlen(pattern)))
        {
            p = ft_strjoin(p, content->d_name, 0);
            p = ft_strjoin(p, " ", 0);
        }
    }
    closedir(d);
    p[ft_strlen(p) - 1] = 0;
    return p;
}

void handle_wildcard(t_lnode *head)
{
    e_token t;
    t_lnode *current;
    char *tmp;
    char *p;

    current = head;
    t = EOL;
    while (get_token(current) != EOL)
    {
        // In case export H=* for example it will check for file starting with H= which is wrong.
        // SHould check only after the '=' character
        if (t != SGLQT && t != DBLQT && get_token(current) == CMD && ft_strchr(get_cmd(current), '*'))
        {
            tmp = current->type.cmd;
            p = open_current_dir(get_cmd(current));
            if (p[0] != 0)
            {
                set_cmd(current, p);
                free(tmp);
            }
        }
        t = get_token(current);
        current = current->next;
    }
}