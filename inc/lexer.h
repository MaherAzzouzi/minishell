#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>

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
} e_token;

typedef struct s_lexer_node
{
	struct s_lexer_node	*next;
	e_token				token;
	char				*cmd;
} t_lnode;

void	ft_lexer(char *str);
e_token	lexer_get_type(char a, char b);

# endif