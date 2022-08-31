/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:53:57 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 22:48:12 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_an_array_having_dlr(char *p, t_exec_struct *exec_s)
{
	char	*result;
	char	*q;
	char	*env;

	result = NULL;
	while (1)
	{
		q = strchr(p, '$');
		if (q == NULL || q[1] == 0)
			break ;
		env = return_env(q);
		result = (char *)malloc((q - p + 1) * sizeof(char));
		if (result == NULL)
			exit(-1);
		ft_memcpy(result, p, q - p);
		result[q - p] = 0;
		result = n_expand_an_array_having_dlr(result, env, q, exec_s);
		free(env);
		free(p);
		p = result;
	}
	return (n_expand_an_array_having_dlr2(result, p));
}

////////
char	*find_env_expand_1(char *result, char *env,
					char *q, t_exec_struct *exec_s)
{
	result = ft_strjoin(result, get_env(env, exec_s, 0), 2);
	result = ft_strjoin(result, q + ft_strlen(env) + 1, 0);
	free(env);
	return (result);
}

char	*find_env_expand(t_lnode *node, t_exec_struct *exec_s)
{
	char	*result;
	char	*q;
	char	*p;
	char	*env;

	if (get_token(node) != CMD)
		return (NULL);
	p = ft_strdup(node->type.cmd);
	while (1)
	{
		q = strchr(p, '$');
		if (q == NULL || (q[1] == 0))
		{
			free(node->type.cmd);
			break ;
		}
		env = return_env(q);
		result = (char *)malloc((q - p + 1) * sizeof(char));
		ft_memcpy(result, p, q - p);
		result[q - p] = 0;
		result = find_env_expand_1(result, env, q, exec_s);
		free(p);
		p = result;
	}
	return (p);
}

t_lnode	*case_of_one_char_dollar(t_lnode **head, t_lnode *current,
		t_exec_struct *exec_s, int se)
{
	t_lnode	*node;
	t_lnode	*p;
	char	*val;

	if (se == 0)
		val = ft_strdup("$$");
	else
		val = get_env(convert_token(get_token(current->next)), exec_s, 0);
	node = ft_new_node_lex(CMD, val);
	free(node->type.cmd);
	node->type.cmd = val;
	if (*head == current)
		*head = node;
	else
	{
		p = *head;
		while (p->next != current)
			p = p->next;
		p->next = node;
	}
	node->next = current->next->next;
	free_lexer_node(current->next);
	free_lexer_node(current);
	return (node->next);
}

void	combine_successive_cmds(t_lnode *head)
{
	t_lnode	*current;
	t_lnode	*tmp;
	int		flag;

	flag = 1;
	while (flag)
	{
		flag = 0;
		current = head;
		while (get_token(current) != EOL)
		{
			if (get_token(current) == CMD && get_token(current->next) == CMD)
			{
				current->type.cmd = ft_strjoin(current->type.cmd,
						current->next->type.cmd, 0);
				tmp = current->next->next;
				free_lexer_node(current->next);
				current->next = tmp;
				flag = 1;
			}
			current = current->next;
		}
	}
}
