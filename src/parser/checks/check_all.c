#include "minishell.h"

void show_error(int ret, char *message)
{
    if (ret == FAIL)
    {
        printf("%s\n", message);
    }
}

int check_all(t_lnode *head)
{
    int ret;

    ret = two_successive_pars(head);
    return ret;
}