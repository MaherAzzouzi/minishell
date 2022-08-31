/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_redr_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:06:39 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:07:36 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lnode	*find_red(t_lnode *head, t_lnode *end, e_token redr)
{
	t_lnode	*current;

	current = head;
	while (current != end && current != NULL)
	{
		if (get_token(current) == redr)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_lnode	*get_command(t_lnode *head, t_lnode *end)
{
	t_lnode	*p;
	e_token	last_token;

	p = head;
	last_token = EOL;
	head = ignore_spaces_ret(head);
	if (get_token(head) == CMD)
		return (head);
	else if (get_token(head) == SGLQT || get_token(head) == DBLQT)
		return (head->next);
	else
	{
		while (p != end)
		{
			if (get_token(p) == CMD && last_token == CMD)
				return (p);
			if (get_token(p) != SPC
				&& get_token(p) != SGLQT && get_token(p) != DBLQT)
				last_token = get_token(p);
			p = p->next;
		}
	}
	return (NULL);
}

int	count_command_with_ore_args(t_lnode *cmd, t_lnode *head, t_lnode *end)
{
	int	counter;

	counter = 0;
	while (head != end)
	{
		if (head == cmd)
			;
		else if (get_token(head) == REDRI || get_token(head) == REDRO
			|| get_token(head) == DLMI || get_token(head) == APPND)
		{
			head = head->next;
			head = ignore_spaces_ret(head);
			if (get_token(head) == SGLQT || get_token(head) == DBLQT)
				head = head->next;
			if (get_token(head) != CMD)
				exit(0);
		}
		else if (get_token(head) == CMD)
			++counter;
		head = head->next;
	}
	return (counter);
}

int	fill_command_with_ore_args(t_lnode *cmd,
		t_lnode *head, char **argv, t_lnode *end)
{
	int	counter;

	counter = 0;
	while (head != end)
	{
		if (head == cmd)
			;
		else if (get_token(head) == REDRI || get_token(head) == REDRO
			|| get_token(head) == DLMI || get_token(head) == APPND)
		{
			head = head->next;
			head = ignore_spaces_ret(head);
			if (get_token(head) == SGLQT || get_token(head) == DBLQT)
				head = head->next;
			if (get_token(head) != CMD)
				exit(0);
		}
		else if (get_token(head) == CMD)
			argv[counter++] = ft_strdup(get_cmd(head));
		head = head->next;
	}
	argv[counter] = NULL;
	return (counter);
}

int	count_redirections(t_lnode *head, e_token redr, t_lnode *end)
{
	t_lnode	*current;
	int		count;

	count = 0;
	current = head;
	while (current != end)
	{
		if (get_token(current) == redr)
			count++;
		current = current->next;
	}
	return (count);
}
