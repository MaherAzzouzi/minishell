/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 22:21:54 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 22:22:41 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKS_H
# define CHECKS_H

int		two_successive_pars(t_lnode *head);
int		check_all(t_lnode *head);
int		check_condt_syntax_errors(t_lnode *head);
int		check_left_right(t_lnode *condt, t_lnode *head);
t_lnode	*return_condt_addr(t_lnode *head);

#endif