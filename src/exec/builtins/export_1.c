/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:21:37 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 21:10:06 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_egale_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_sort_export(t_envp *head)
{
	t_envp	*current;
	t_envp	*front;
	char	*temp;
	int		i;

	i = 0;
	current = head;
	while (current)
	{
		front = current->next;
		while (front)
		{
			if (ft_strcmp(current->str, front->str) > 0)
			{
				temp = current->str;
				current->str = front->str;
				front->str = temp;
			}
			front = front->next;
		}
		current = current->next;
	}
}

void	print_exp(int len, char *str, int *i)
{
	ft_printf("declare -x ");
	while ((*i) <= len)
	{
		ft_printf("%c", str[(*i)]);
		(*i)++;
	}
	ft_printf("\"");
	while (str[(*i)])
	{
		ft_printf("%c", str[(*i)]);
		(*i)++;
	}
	ft_printf("\"");
	ft_printf("\n");
}

void	p_(char *str, int len)
{
	int	i;

	i = 0;
	if (len != -1)
		print_exp(len, str, &i);
	else
	{
		ft_printf("declare -x ");
		while (str[i])
		{
			ft_printf("%c", str[i]);
			i++;
		}
		ft_printf("\n");
	}
}

int	checking_new_env(t_parsing_node *node, t_envp **env, t_envp *export)
{
	int	i;
	int	t;

	i = 1;
	while (node->cmd.argv[i])
	{
		t = check_new_env(node->cmd.argv[i], env);
		if (check_export_syntax(node->cmd.argv[i]) == -1
			|| ft_check_var_syntx(node->cmd.argv[i]) == 0)
		{
			free_env(&export);
			ft_putstr_fd("not a valid identifier\n", 2);
			return (FAIL);
		}
		else if (check_export_syntax(node->cmd.argv[i]) == 1 && t == 0)
			new_env(env, node->cmd.argv[i]);
		i++;
	}
	return (SUCCESS);
}
