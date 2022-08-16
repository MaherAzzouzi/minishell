/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:46:14 by snagat            #+#    #+#             */
/*   Updated: 2022/06/10 18:39:44 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include <stdio.h>

int	ft_check_siblings(t_lnode	*head, e_token dlm)
{
	t_lnode *current;
	int		b;

	b = 0;
	current = head;
	ft_check_lists(current);
	while (current)
	{
		if (get_token(current) == dlm)
		{
			b = 1;
			current = current->next;
			while (	get_token(current) != dlm
			&&		get_token(current) != PIPE
			&&		get_token(current) != EOL)
			{
				current = current->next;
			}
			if (get_token(current) == dlm)
				b = 0;
		}
		current = current->next;
	}
	//printf("b is  %d\n", b);
	if (b == 0)
		return(SUCCESS);
	else
		return(FAIL);
}


void	ft_check_lists(t_lnode  *head)
{
	t_lnode		*current;

	current = head;

	if (head == NULL)
		exit(1);
	while (current)
	{
		// if and else should bot be uncommented for logs!
		 if (get_token(current) == CMD)
			printf("[token = %s] [cmd = %s]\n", enum_to_str(current->type.token), current->type.cmd);
		 else
			printf("[token = %s]\n", enum_to_str(current->type.token));
		current = current->next;
	}
}