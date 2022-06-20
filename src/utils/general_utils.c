#include "minishell.h"
#include "lexer.h"
#include "parser.h"

int is_empty(char *p)
{
    return (p && p[0] == 0);
}

void log_(t_lnode *head)
{
	printf("--------------------\n");
	ft_check_lists(head);
	printf("--------------------\n");
}