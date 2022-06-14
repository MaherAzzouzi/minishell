# ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "lexer.h"
# include "parser.h"


t_lnode *find_o_red(t_lnode *head);
t_lnode *find_i_red(t_lnode *head);
t_parsing_node *parse_redirections(t_lnode *head);


# endif