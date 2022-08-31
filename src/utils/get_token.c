/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:47:14 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:47:34 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

e_token	get_token(t_lnode *node)
{
	return (node->type.token);
}

void	set_token(t_lnode *node, e_token e)
{
	node->type.token = e;
}
