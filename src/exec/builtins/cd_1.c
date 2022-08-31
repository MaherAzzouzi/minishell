/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:16:08 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:16:52 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(char *str, t_envp *env)
{
	t_envp	*curr;
	char	*path;
	char	*env_var;

	curr = env;
	path = NULL;
	while (curr)
	{
		env_var = ft_strdup(curr->str);
		path = ft_strchr(env_var, '=');
		*path = 0;
		if (ft_strcmp(str, env_var) == 0)
		{
			path++;
			path = ft_strdup(path);
			free(env_var);
			return (path);
		}
		free(env_var);
		curr = curr->next;
	}
	return (NULL);
}

int	change_dir_old(char *str, t_envp *env)
{
	char	*path;

	path = find_env(str, env);
	if (!path)
	{
		ft_putstr_fd("Couldnt find path\n", 2);
		return (FAIL);
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("Couldnt change directory\n", 2);
		return (FAIL);
	}
	free(path);
	return (SUCCESS);
}

char	*get_cwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	return (cwd);
}

void	updating_envs(char *curr_path, t_envp *en, char *new_path)
{
	update_env(&en, ft_strdup("OLDPWD"), curr_path);
	new_path = get_cwd();
	if (!new_path)
		new_path = find_env("OLDPWD", en);
	update_env(&en, ft_strdup("PWD"), new_path);
	free(new_path);
}

int	change_dir(char *dir, t_envp *en)
{
	char	*curr_path;
	char	*new_path;

	new_path = NULL;
	curr_path = get_cwd();
	if (!curr_path && errno == ENOENT)
		curr_path = find_env("PWD", en);
	if (!ft_strcmp(dir, ".") && errno == ENOENT)
	{
		free(curr_path);
		ft_putstr_fd("Couldnt find dir\n", 2);
		return (FAIL);
	}
	if (chdir(dir) == -1)
	{
		free(curr_path);
		ft_putstr_fd("Directory not found\n", 2);
		return (FAIL);
	}
	else
		updating_envs(curr_path, en, new_path);
	free(curr_path);
	return (SUCCESS);
}
