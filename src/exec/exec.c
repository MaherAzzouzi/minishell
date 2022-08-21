#include "minishell.h"

char *return_cmd_full_path(t_parsing_node *root, t_exec_struct *exec_s)
{
	char *p;

	if (root->cmd.cmd[0] == '.' && root->cmd.cmd[1] == '/')
	{
		p = getcwd(NULL, 0);
		p = ft_strjoin(p, &root->cmd.cmd[1], 0);
	}
	else if (root->cmd.cmd[0] != '/' && root->cmd.cmd[0] != 0)
	{
		p = check_if_bin_exist(root->cmd.cmd, exec_s->path);
	}
	else
	{
		p = root->cmd.cmd;
	}
	return p;
}

pid_t spawn_process(int in, int out, t_parsing_node *root, t_exec_struct *exec_s, int *fd, t_envp **env)
{
	pid_t pid;
	char *p;
	struct stat sb;

	// printf("Executing %s\n", root->cmd.cmd);
	if (is_builtin(root))
	{
		int stdout_ = dup(1);
		int stdin_ = dup(0);
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
		handle_herdoc_iredr(root, exec_s);
		handle_append_oredr(root);
		expand_one_node(root, exec_s);
		builtins(root, exec_s, env);
		dup2(stdout_, 1);
		dup2(stdin_, 0);
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
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
		close(fd[0]);
		close(fd[1]);
		if (root->p.parenthesised == 0)
		{
			p = NULL;
			if (root->cmd.cmd[0] != 0)
			{
			expand_one_node(root, exec_s);
			p = return_cmd_full_path(root ,exec_s);
			if (p == NULL)
				show_errno(root->cmd.cmd);
			if (stat(p, &sb) < 0)
				show_errno(p);
			if (S_ISDIR(sb.st_mode))
			{
				printf("minishell: %s: is a directory\n", p);
				exit(-2);
			}
			}
			handle_herdoc_iredr(root, exec_s);
			handle_append_oredr(root);
			if (root->cmd.cmd[0] == 0)
			{
				p = "/";
				root->cmd.argv[0] = "/";
			}
			execve(p, root->cmd.argv, exec_s->envp);
			exit(0);
		}
		else
		{
			// printf("HANDLE PARANTHESIS!\n");
			handle_herdoc_iredr(root, exec_s);
			handle_append_oredr(root);
			int ret = core(ft_strdup(root->p.cmd), exec_s->envp, exec_s, env);
			exit(ret);
		}
	}
	else
	{
		if (in != 0)
			close(in);
		if (out != 1)
			close(out);
		return (pid);
	}
	return 0;
}

void pipe_chain_exec(t_parsing_node *node, t_exec_struct *exec_s, t_envp **env)
{
	static int fd[2];
	int status;
	int pid2;
	int fd2;

	fd2 = dup(0);
	while (node->type == PIPE)
	{
		// printf("HERE1\n");
		int ret = pipe(fd);
		if (ret < 0)
			exit(-1);
		spawn_process(0, fd[1], node->lchild, exec_s, fd, env);
		if (node->rchild->type == CMD)
		{
			// printf("HERE IM PIPE\n");
			pid2 = spawn_process(fd[0], 1, node->rchild, exec_s, fd, env);
			waitpid(pid2, &status, 0);
			if (WIFEXITED(status))
			{
				exec_s->exit_status = status;
				// printf("Exit status is %d\n", WEXITSTATUS(status));
			}
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
	while (waitpid(-1, &status, 0) != -1)
		;
}

int exec_simple_cmd(t_parsing_node *node, t_exec_struct *exec_s, t_envp **env)
{
	pid_t	pid;
	char	*p;
	int		status;
	int		es;
	struct stat sb;

	if (is_builtin(node))
	{
		int stdout_ = dup(1);
		int stdin_ = dup(0);
		handle_herdoc_iredr(node, exec_s);
		handle_append_oredr(node);
		expand_one_node(node, exec_s);
		builtins(node, exec_s, env);
		dup2(stdout_, 1);
		dup2(stdin_, 0);
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		if (node->p.parenthesised == 0)
		{
			p = NULL;
			if (node->cmd.cmd[0] != 0)
			{
				expand_one_node(node, exec_s);
				p = return_cmd_full_path(node ,exec_s);
				if (p == NULL)
					show_errno(node->cmd.cmd);
				if (stat(p, &sb) < 0)
					show_errno(p);
				if (S_ISDIR(sb.st_mode))
				{
					printf("minishell: %s: is a directory\n", p);
					exit(-2);
				}
			}
			handle_herdoc_iredr(node, exec_s);
			handle_append_oredr(node);
			if (node->cmd.cmd[0] == 0)
			{
				p = "/";
				node->cmd.argv[0] = "/";
			}
			execve(p, node->cmd.argv, exec_s->envp);
			exit(0);
		}
		else
		{
			// printf("HANDLE PARANTHESIS!\n");
			handle_herdoc_iredr(node, exec_s);
			handle_append_oredr(node);
			int ret = core(ft_strdup(node->p.cmd), exec_s->envp, exec_s, env);
			exit(ret);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			es = status;
			g_exec_struct->exit_status = es;
			return es;
		}
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) != 11)
			{
				printf("Quit: %d\n", WTERMSIG(status));
				exec_s->exit_status |= ((128 + WTERMSIG(status)) << 8) & 0xff00;
			}
		}
	}
	return 0;
}

void execute(t_parsing_node *root, t_exec_struct *exec_s, char *envp[], t_envp **env)
{
	(void)envp;
	free(exec_s->path);
	exec_s->path = get_env("PATH", exec_s, 0);
	if (root->type == CMD)
		exec_simple_cmd(root, exec_s, env);
	else if (root->type == PIPE)
		pipe_chain_exec(root, exec_s, env);
	else if (root->type == OR)
		or_chain_exec(root, exec_s, *env);
	else if (root->type == AND)
		and_chain_exec(root, exec_s, *env);
}
