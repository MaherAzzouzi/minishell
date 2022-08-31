/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 23:14:02 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 23:14:18 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

int		is_empty(char *p);
int		is_even(int num);
int		is_odd(int num);
void	ignore_spaces(t_lnode **head);
void	free_tree(t_parsing_node *root);
int		count_token(t_lnode *head, t_lnode *current, t_token t);
void	free_node(t_parsing_node *node);
t_lnode	*get_end(t_lnode *head);
void	log_(t_lnode *head);
void	free_all(char *cmd, t_lnode *head, t_parsing_node *root);
void	preorder_show(t_parsing_node *root);

#endif