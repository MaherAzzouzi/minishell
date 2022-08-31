/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:17:26 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:17:28 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir_home(char *dir, t_envp *env)
{
	char	*path;
	char	*curr_path;
	char	*pwd;

	curr_path = get_cwd();
	path = find_env(dir, env);
	if (!path)
	{
		ft_putstr_fd("couldnt find path", 2);
		return (FAIL);
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("couldnt change directory\n", 2);
		return (FAIL);
	}
	update_env(&env, ft_strdup("OLDPWD"), curr_path);
	pwd = get_cwd();
	update_env(&env, ft_strdup("PWD"), pwd);
	free(path);
	free(curr_path);
	free(pwd);
	return (SUCCESS);
}

int	ft_cd(t_parsing_node *root, t_envp *en)
{
	int	t;

	t = SUCCESS;
	if (!(ft_strcmp(root->cmd.argv[0], "cd")) && root->cmd.argv[1] == NULL)
		t = change_dir_home("HOME", en);
	else if (!((ft_strcmp(root->cmd.argv[1], "-"))))
		t = change_dir_old("OLDPWD", en);
	else
		t = change_dir(root->cmd.argv[1], en);
	if (t == SUCCESS)
	{
		convert(en);
		exit_status_success();
		return (SUCCESS);
	}
	exit_status_fail();
	return (FAIL);
}
