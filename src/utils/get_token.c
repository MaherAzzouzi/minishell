#include "lexer.h"
#include "minishell.h"
#include "parser.h"


e_token get_token(t_lnode *node)
{
    return(node->type.token);
}

void set_token(t_lnode *node, e_token e)
{
    node->type.token = e;
}