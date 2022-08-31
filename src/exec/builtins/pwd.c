/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:22:57 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:22:59 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_parsing_node *node, t_envp *env)
{
	char	*str;
	char	cwd[1000];

	str = NULL;
	if (ft_strcmp(node->cmd.argv[0], "pwd") == 0)
	{
		str = getcwd(cwd, 1000);
		if (str == NULL)
		{
			str = find_env("PWD", env);
			printf("%s\n", str);
		}
		else
			printf("%s\n", str);
		if (!str)
			free(str);
		return (SUCCESS);
	}
	else
	{
		printf("invalid arguments\n");
		return (FAIL);
	}
}
