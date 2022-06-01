/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazzouzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:05:01 by mazzouzi          #+#    #+#             */
/*   Updated: 2021/11/11 15:05:47 by mazzouzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*q;

	p = 0;
	if (lst == 0 || f == 0)
		return (0);
	while (lst)
	{
		q = ft_lstnew((*f)(lst->content));
		if (q == 0)
		{
			ft_lstclear(&p, del);
			break ;
		}
		ft_lstadd_back(&p, q);
		lst = lst->next;
	}
	return (p);
}
