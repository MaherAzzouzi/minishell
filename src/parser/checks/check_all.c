/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:43:38 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 18:43:41 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_error(int ret, char *message)
{
	if (ret == FAIL)
	{
		printf("%s\n", message);
	}
}

int	check_all(t_lnode *head)
{
	int	ret;

	ret = two_successive_pars(head);
	if (ret == FAIL)
		return (FAIL);
	ret = check_condt_syntax_errors(head);
	if (ret == FAIL)
		return (FAIL);
	ret = check_left_par(head);
	if (ret == FAIL)
		return (FAIL);
	return (ret);
}
