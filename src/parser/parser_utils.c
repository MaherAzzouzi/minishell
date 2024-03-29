/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:13:32 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 22:48:12 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(t_lnode *node)
{
	return ((get_token(node) == DBLQT) || (get_token(node) == SGLQT));
}

void	consolidate_commands(t_lnode **head)
{
	t_lnode	*current;
	t_lnode	*p;
	t_lnode	*tmp;

	current = *head;
	while (get_token(current) != EOL)
	{
		if (get_token(current) == CMD
			&& is_quote(current->next) && get_token(current->next->next) == CMD)
		{
			set_cmd(current->next->next, ft_strjoin(get_cmd(current),
					get_cmd(current->next->next), 1));
			tmp = current;
			if (current == *head)
				*head = current->next;
			else
				p->next = current->next;
			current = current->next;
			free_lexer_node(tmp);
		}
		p = current;
		current = current->next;
	}
}

void	replace(char *p, char a, char b)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i] == a)
			p[i] = b;
		i++;
	}
}

void	replace_dlr_with_flag(t_lnode *head)
{
	t_lnode	*current;

	current = head;
	while (get_token(current) != EOL)
	{
		if (get_token(current) == SGLQT)
		{
			current = current->next;
			while (get_token(current) != SGLQT)
			{
				if (get_token(current) == CMD)
				{
					if (!strchr(get_cmd(current), '\xff'))
						replace(get_cmd(current), '$', '\xff');
				}
				current = current->next;
			}
		}
		current = current->next;
	}
}

void	flag_env_variables(t_lnode *head)
{
	int		size;
	char	*p;

	while (get_token(head) != EOL)
	{
		if (get_token(head) == CMD && strchr(get_cmd(head), '$'))
		{
			size = ft_strlen(head->type.cmd);
			p = (char *)malloc((size + 2) * sizeof(char));
			ft_memset(p, 0, size + 2);
			ft_memcpy(p, head->type.cmd, size);
			p[size] = '\xfe';
			free(head->type.cmd);
			head->type.cmd = p;
		}
		head = head->next;
	}
}
