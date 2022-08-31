/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:18:19 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:18:20 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(t_envp **en, char *str, char *path)
{
	t_envp	*current;
	char	*fr;

	fr = NULL;
	current = *en;
	while (current)
	{
		if (!ft_strncmp(current->str, str, ft_strlen(str)))
		{
			free(current->str);
			fr = ft_strjoin(str, "=", 3);
			current->str = ft_strjoin(fr, path, 0);
		}
		current = current->next;
	}
	free(str);
}
