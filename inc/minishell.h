/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:27:59 by snagat            #+#    #+#             */
/*   Updated: 2022/06/08 14:33:22 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "lexer.h"
# include "parser.h"
# include "utils.h"
# include "libft.h"

# define INFINIT    666
# define RED        "\033[0;31m"
# define GREEN		"\033[0;32m"
# define WHITE		"\033[0;37m"
# define SUCCESS     0
# define FAIL       -1
# define FOUND      1
# define NOT_FOUND  0

void    free_list(t_lnode **head);



#endif