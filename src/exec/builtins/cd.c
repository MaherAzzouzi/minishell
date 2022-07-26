#include "minishell.h"

void	change_dir(char *dir, t_exec_struct *exec_s, int f)
{
	char *path;
	if (f == 1)
		path = get_env(dir, exec_s, 0);
	else
		path = dir;
	if (!path)
		perror("couldnt find env variable");
	if (chdir(path) != 0)
		exit(-1);
}


void    ft_cd(t_parsing_node *root,t_exec_struct *exec_s)
{
	char cwd[1000];
	char	*str;

	str = NULL;
	if (!(ft_strcmp(root->cmd.argv[0], "cd")) && root->cmd.argv[1] == NULL)
		change_dir("HOME", exec_s, 1);
	else if (!((ft_strcmp(root->cmd.argv[1], "-"))))
		change_dir("OLDPWD", exec_s, 1);
	else
		change_dir(root->cmd.argv[1], exec_s, 0);
	str = getcwd(cwd, 1000);
	printf("%s\n", str);


}