#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
typedef enum {
	SGLQT,
	DBLQT,
	REDRI,
	REDRO,
	DLMI,
	APPND,
	PIPE,
	DLR,
	CMD,
	EOL,
	SPACE,
} e_token;

typedef	struct s_type
{
	e_token	token;
	char	*cmd;
} t_type;


typedef struct s_lexer_node
{
	struct s_lexer_node	*next;
	t_type				type;
} t_lnode;

void	ft_lexer(char *str);
t_lnode	*ft_new_node_lex(e_token token, char *cmd);
t_lnode	*ft_add_back_lex(t_lnode **head, e_token token, char *cmd);
e_token	lexer_get_type(char a, char b);

# endif