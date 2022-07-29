#include "minishell.h"

char *find_env(char *str, t_envp *env)
{
	t_envp *curr;
	char *path;

	curr = env;
	path = NULL;
	while(curr)
	{
		if (ft_strncmp(str, curr->str, ft_strlen(str)) == 0)
		{
			path = ft_strchr(curr->str, '=');
			path++;
			return(path);
		}
		curr = curr->next;
	}
	return(NULL);
}
int	change_dir_old(char *str ,t_envp *env)
{
	char *path;

	path = find_env(str, env);
	if (!path)
	{
		ft_putstr_fd("couldnt find path\n", 2);
		return(FAIL);
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("couldnt change directory\n", 2);
		return(FAIL);
	}
	return(SUCCESS);
}
char *get_cwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	return(cwd);
	
}
int	change_dir(char *dir, t_envp *en)
{
	char *curr_path;

	curr_path = get_cwd();
	if (!curr_path && errno == ENOENT)
		curr_path = find_env("PWD", en);
	if ((!ft_strcmp(dir, "..") || !ft_strcmp(dir,  ".")) && errno == ENOENT)
	{
		ft_putstr_fd("couldnt find dir\n", 2);
		return(FAIL);
	}
	if (!curr_path && errno == ENOENT)
		curr_path = find_env("PWD", en);
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("directory not found", 2);
		return(FAIL);
	}
	else
	{
		printf("%s\n", get_cwd());
		update_env(&en, "OLDPWD", curr_path);
		update_env(&en, "PWD", get_cwd());
	}
	return(SUCCESS);
}

int	change_dir_home(char *dir, t_exec_struct *exec_s, t_envp *env)
{
	char *path;
	char *curr_path;

	curr_path = get_cwd();


	path = get_env(dir, exec_s, 0);
	if (!path)
	{
		ft_putstr_fd("couldnt find path", 2);
		return(FAIL);
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("couldnt change directory\n", 2);
		return(FAIL);
	}
	update_env(&env, "OLDPWD", curr_path);
	update_env(&env, "PWD", get_cwd());
	return(SUCCESS);
}

int    ft_cd(t_parsing_node *root,t_exec_struct *exec_s, t_envp *en)
{
	int t;

	t = SUCCESS;
	if (!(ft_strcmp(root->cmd.argv[0], "cd")) && root->cmd.argv[1] == NULL)
		t = change_dir_home("HOME", exec_s, en);
	else if (!((ft_strcmp(root->cmd.argv[1], "-"))))
		t = change_dir_old("OLDPWD", en);
	else
		t = change_dir(root->cmd.argv[1], en);
	if (t == SUCCESS)
		return(SUCCESS);
	return(FAIL);
}