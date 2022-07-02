#include "minishell.h"

char *return_cmd_full_path(t_parsing_node *root, t_exec_struct *exec_s)
{
	char *p;

	if (root->cmd.cmd[0] != '/')
		p = check_if_bin_exist(root->cmd.cmd, exec_s->path);
	else
		p = root->cmd.cmd;
	return p;
}

void ft_close(int fd, int p)
{
	if (p)
		write(1, "PARENT :", 9);
	else
		write(1, "CHILD :", 8);
	printf("%d\n", fd);
	close(fd);
}

void ft_pipe(int *fd)
{
	pipe(fd);
	printf("pipe : %d %d\n", fd[0], fd[1]);
}

pid_t spawn_process(int in, int out, t_parsing_node *root, t_exec_struct *exec_s, int *fd)
{
	pid_t pid;

	printf("Executing %s\n", root->cmd.cmd);
	pid = fork();
	if (pid == 0)
	{
		char *p;

		if (in != 0)
		{
			dup2(in, 0);
		   close(in);
		}
		if (out != 1)
		{ 
			dup2(out, 1);
		   close(out);
		}
		p = return_cmd_full_path(root ,exec_s);
		if (p == NULL)
			show_errno();
		close(fd[0]);
		close(fd[1]);
		execve(p, root->cmd.argv, exec_s->envp);
		exit(0);
	   
	}
	else
	{
		// waitpid(-1, 0, 0);
		if (in != 0)
		{
			close(in);
		}
			// close(in);
		if (out != 1)
			close(out);
		return (pid);
	}
}

void show_content(int fd)
{
	char p[4096];
	int ret;

	ret = read(fd, p, 4096);
	write(1, p, ret);
}

void recursive_exec(t_parsing_node *node, t_exec_struct *exec_s)
{
	static int fd[2];
	int status;
	int pid1;
	int pid2;
	int fd2;
	

	fd2 = dup(0);
	while (node->type == PIPE)
	{
		pipe(fd);
		pid1 = spawn_process(0, fd[1], node->lchild, exec_s, fd);
		if (node->rchild->type == CMD)
		{
			pid2 = spawn_process(fd[0], 1, node->rchild, exec_s, fd);
			// waitpid(pid1, &status, 0);
			waitpid(pid2, &status, 0);
		}
		else
		{
			dup2(fd[0], 0);
			close(fd[0]);
		}
		node = node->rchild;
	}
	dup2(fd2, 0);
	close(fd2);
	while(waitpid(-1, &status, 0) != -1);
}


void	exec_simple_cmd(t_parsing_node *root, t_exec_struct *exec_s)
{
	// int status;
	pid_t	pid;
	char	*p;

	pid = fork();
	if (pid == 0)
	{
		p = return_cmd_full_path(root ,exec_s);
		if (p == NULL)
			show_errno();
		execve(p, root->cmd.argv, exec_s->envp);
		exit(0);
	}
	else
		while(waitpid(-1, 0, 0) != -1);
}


// void recursive_exec(t_parsing_node *node, t_exec_struct *exec_s)
// {
//     // int pid;
//     // int status;
//     int fd[2];

//     if (node->type == PIPE)
//     {
//         ft_pipe(fd);
//         spawn_process(0, fd[1], node->lchild, exec_s,fd);
//         //waitpid(pid, &status, 0);
//         spawn_process(fd[0], 1, node->rchild, exec_s,fd);
//     }
// }

void execute(t_parsing_node *root, t_exec_struct *exec_s, char *envp[])
{
	init(exec_s, envp);
	builtins(root);

	//spawn_process(0, 1, root, exec_s);
	if (root->type == CMD)
		exec_simple_cmd(root, exec_s);
	else
		recursive_exec(root, exec_s);
}