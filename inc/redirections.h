/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 23:14:32 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 23:14:55 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "lexer.h"
# include "parser.h"

t_lnode			*find_o_red(t_lnode *head, t_lnode *end, t_token t);
t_lnode			*find_i_red(t_lnode *head, t_lnode *end, t_token t);
t_parsing_node	*parse_redirections(t_lnode *head, t_lnode *end);

#endif