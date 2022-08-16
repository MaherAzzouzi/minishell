#include "minishell.h"

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

void open_current_dir(char *pattern)
{
    DIR *d;
    struct dirent *content;

    d = opendir(".");
    while (1)
    {
        content = readdir(d);
        if (content == NULL)
            break;
        if (content->d_name[0] != '.' &&
        is_matching(content->d_name, pattern, strlen(content->d_name), strlen(pattern)))
            printf("%s\n", content->d_name);
    }
    closedir(d);
}

int main() {
    char *p = "in*st";
    char *s = "includes";
    int ret = is_matching(s, p, strlen(s), strlen(p));
    open_current_dir("*.c");
    printf("ret %d\n", ret);
}