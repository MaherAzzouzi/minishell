/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:52:33 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 15:05:03 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*p;

	if (lst == 0 || f == 0)
		return ;
	p = lst;
	while (p)
	{
		(*f)(p->content);
		p = p->next;
	}
}
