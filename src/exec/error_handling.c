#include "minishell.h"

int show_errno(char *file)
{
    printf("minishell: %s: %s\n", file, strerror(errno));
    exit(-1);
}