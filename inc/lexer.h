/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:23:48 by snagat            #+#    #+#             */
/*   Updated: 2022/08/31 23:31:38 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

typedef enum e_token{
	SGLQT,
	DBLQT,
	REDRI,
	REDRO,
	DLMI,
	APPND,
	PIPE,
	CMD,
	EOL,
	SPC,
	RPAR,
	LPAR,
	OR,
	AND,
	DLR,
	LEFT_PAR,
	RIGHT_PAR,
}	t_token;

typedef struct s_type
{
	t_token	token;
	char	*cmd;
}	t_type;

typedef struct s_lexer_node
{
	struct s_lexer_node	*next;
	t_type				type;
	char				*parenthesis_start;
}	t_lnode;

t_lnode	*ft_lexer(char *str);
t_lnode	*ft_new_node_lex(t_token token, char *cmd);
t_lnode	*ft_add_back_lex(t_lnode **head, t_token token, char *cmd);
t_token	lexer_get_type(char a, char b);
char	*enum_to_str(t_token token);
void	set_token(t_lnode *node, t_token e);
void	set_cmd(t_lnode *node, char *cmd);
char	*get_cmd(t_lnode *node);
t_token	get_token(t_lnode *node);
void	free_lexer_node(t_lnode *node);
t_lnode	*lex(char *cmd);
#endif