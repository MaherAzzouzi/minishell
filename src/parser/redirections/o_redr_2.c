/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_redr_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:08:44 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:12:22 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	n_parse_herdoc(t_lnode *head, struct herdoc_exp **redri_array,
			e_token redr, int *i)
{
	struct herdoc_exp	*herdoc;

	if (get_token(head) == redr)
	{
		herdoc = (struct herdoc_exp *)malloc(sizeof(struct herdoc_exp));
		herdoc->is_quoted = 0;
		head = head->next;
		while (get_token(head) == SPC)
			head = head->next;
		if (get_token(head) == SGLQT || get_token(head) == DBLQT)
		{
			herdoc->is_quoted = 1;
			head = head->next;
		}
		if (get_token(head) != EOL)
		{
			herdoc->herdoc_keyword = ft_strdup(get_cmd(head));
			redri_array[(*i)++] = herdoc;
		}
	}
}

struct herdoc_exp	**alloc_herdoc_array(t_lnode *head,
		e_token redr, t_lnode *end)
{
	int					count;
	int					i;
	struct herdoc_exp	**redri_array;

	count = count_redirections(head, redr, end);
	redri_array = (struct herdoc_exp **)malloc((count + 1)
			* sizeof(struct herdoc_exp *));
	i = 0;
	if (!redri_array)
		exit(0);
	while (head != end && head != NULL)
	{
		n_parse_herdoc(head, redri_array, redr, &i);
		head = head->next;
	}
	redri_array[i] = NULL;
	return (redri_array);
}

char	**alloc_redr_array(t_lnode *head, e_token redr, t_lnode *end)
{
	int		count;
	int		i;
	char	**redri_array;

	count = count_redirections(head, redr, end);
	redri_array = (char **)malloc((count + 1) * sizeof(char *));
	i = 0;
	if (!redri_array)
		exit(0);
	while (head != end && head != NULL)
	{
		if (get_token(head) == redr)
		{
			head = head->next;
			while (get_token(head) == SPC)
				head = head->next;
			if (get_token(head) == SGLQT || get_token(head) == DBLQT)
				head = head->next;
			if (get_token(head) != EOL)
				redri_array[i++] = ft_strdup(get_cmd(head));
		}
		head = head->next;
	}
	redri_array[i] = NULL;
	return (redri_array);
}

e_token	get_last_output_red(t_lnode *head)
{
	e_token	t;

	t = EOL;
	while (get_token(head) != EOL)
	{
		if (get_token(head) == REDRO || get_token(head) == APPND)
			t = get_token(head);
		head = head->next;
	}
	return (t);
}

e_token	get_last_in_red(t_lnode *head)
{
	e_token	t;

	t = EOL;
	while (get_token(head) != EOL)
	{
		if (get_token(head) == DLMI || get_token(head) == REDRI)
			t = get_token(head);
		head = head->next;
	}
	return (t);
}
