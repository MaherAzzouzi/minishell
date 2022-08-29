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

static void	updating_envs(char *curr_path, t_envp *en, char *new_path)
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

int	change_dir_home(char *dir, t_envp *env)
{
	char	*path;
	char	*curr_path;
	char	*new_path;
	char	*pwd;

	curr_path = get_cwd();
	path = find_env(dir, env);
	new_path = NULL;
	(void)new_path;
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
