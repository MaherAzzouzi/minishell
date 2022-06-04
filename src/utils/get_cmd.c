#include "lexer.h"
#include "minishell.h"
#include "parser.h"


char    *get_cmd(t_lnode *node)
{
    return(node->type.cmd);
}

void    set_cmd(t_lnode *node, char *cmd)
{
    node->type.cmd = cmd;
}