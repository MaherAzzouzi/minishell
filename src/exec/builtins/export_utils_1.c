/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:20:01 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:23:45 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_envp **head)
{
	t_envp	*curr;
	t_envp	*temp;

	curr = *head;
	while (curr)
	{
		temp = curr;
		if (curr->str)
			free(curr->str);
		curr = curr->next;
		free(temp);
	}
	*head = 0;
}

int	ft_isalnum2(int c)
{
	return ((c <= 'z' && c >= 'a')
		|| (c <= 'Z' && c >= 'A') || (c <= '9' && c >= '0'));
}

char	*ft_strndup(char *str, int j)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * j + 1);
	i = 0;
	while (i < j)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

int	ft_check_var_syntx(char *str)
{
	int	i;

	i = 0;
	while (i < ft_egale_len(str) - 1)
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	set_ar_w_e_o_n(char **s, char *str)
{
	if (check_equal(str) == 2)
		*s = ft_strndup(str, ft_egale_len(str) - 1);
	else if (check_equal(str) == 3)
		*s = ft_strdup(str);
	else
		*s = ft_strndup(str, ft_egale_len(str));
}
