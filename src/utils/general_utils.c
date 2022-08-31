#include "minishell.h"
#include "lexer.h"
#include "parser.h"

int is_empty(char *p)
{
    return (p && p[0] == 0);
}
