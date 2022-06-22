#include "minishell.h"

int show_errno()
{
    printf("Error opening file : %s\n", strerror(errno));
    exit(-1);
}