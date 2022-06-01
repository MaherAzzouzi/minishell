/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:20:26 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 15:05:52 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*p;
	t_list	*q;

	if (lst == 0 || *lst == 0)
		return ;
	p = *lst;
	q = p->next;
	while (1)
	{
		ft_lstdelone(p, del);
		p = q;
		if (q == 0)
			break ;
		q = q->next;
	}
	*lst = 0;
}
