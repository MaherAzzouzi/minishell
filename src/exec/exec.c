#include "minishell.h"
int g_flag = 1;

void ctrl_child(int p)
{
	(void)p;
	return;
}

char *return_cmd_full_path(t_parsing_node *root, t_exec_struct *exec_s)
{
	char *p = NULL;

	p = root->cmd.cmd;
	if (root->cmd.cmd[0] == '.' && root->cmd.cmd[1] == '/')
	{
		p = getcwd(NULL, 0);
		p = ft_strjoin(p, &root->cmd.cmd[1], 0);
	}
	else if (root->cmd.cmd[0] != '/' && root->cmd.cmd[0] != '.')
	{
		p = check_if_bin_exist(root->cmd.cmd, exec_s->path);
	}
	return p;
}

pid_t spawn_process(int in, int out, t_parsing_node *root, t_exec_struct *exec_s, int *fd, t_envp **env)
{
	pid_t pid;
	char *p;
	struct stat sb;

	// printf("Executing %s\n", root->cmd.cmd);

	pid = fork();
	if (pid == 0)
	{
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
			handle_append_oredr(root);
			handle_herdoc_iredr(root, exec_s);
			expand_one_node(root, exec_s);
			builtins(root, exec_s, env);
			dup2(stdout_, 1);
			dup2(stdin_, 0);
			exit (0);
		}
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
		if (it_has_herdoc(root))
		{
			dup2(root->fd[0], 0);
			close(root->fd[0]);
		}
		if (root->p.parenthesised == 0)
		{
			p = NULL;
			if (root->cmd.cmd[0] != 0)
			{
				expand_one_node(root, exec_s);
				p = return_cmd_full_path(root, exec_s);
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
			handle_append_oredr(root);
			handle_herdoc_iredr(root, exec_s);
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
			handle_append_oredr(root);
			handle_herdoc_iredr(root, exec_s);
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
		if (it_has_herdoc(node->lchild))
		{
			close(fd[0]);
			fd[0] = node->lchild->fd[0];
		}
		else
			spawn_process(0, fd[1], node->lchild, exec_s, fd, env);
		if (node->rchild->type == CMD)
		{
			// printf("HERE IM PIPE\n");
			if (it_has_herdoc(node->rchild))
			{
				close(fd[0]);
				fd[0] = node->rchild->fd[0];
			}
			pid2 = spawn_process(fd[0], 1, node->rchild, exec_s, fd, env);
			waitpid(pid2, &status, 0);
			if (WIFEXITED(status))
			{
				exec_s->exit_status = status;
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
	pid_t pid;
	char *p;
	int status;
	int es;
	struct stat sb;


	if (is_builtin(node))
	{
		int stdout_ = dup(1);
		int stdin_ = dup(0);
		handle_append_oredr(node);
		handle_herdoc_iredr(node, exec_s);
		expand_one_node(node, exec_s);
		builtins(node, exec_s, env);
		dup2(stdout_, 1);
		dup2(stdin_, 0);
		return (0);
	}

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, ctrl_c_handler);
	pid = fork();
	if (pid == 0)
	{
		if (it_has_herdoc(node))
		{
			dup2(node->fd[0], 0);
			close(node->fd[0]);
		}
		if (node->p.parenthesised == 0)
		{
			p = NULL;
			if (node->cmd.cmd[0] != 0)
			{
				expand_one_node(node, exec_s);

				p = return_cmd_full_path(node, exec_s);
				if (p == NULL)
					show_errno(node->cmd.cmd);
				if (stat(p, &sb) < 0)
					show_errno(p);
				if (S_ISDIR(sb.st_mode))
				{
					printf("minishell: %s: is a directory\n", node->cmd.cmd);
					exit(-2);
				}
				if (access(p, X_OK) != 0)
				{
					show_errno(node->cmd.cmd);
				}
			}
			handle_append_oredr(node);
			handle_herdoc_iredr(node, exec_s);
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
			handle_append_oredr(node);
			handle_herdoc_iredr(node, exec_s);
			int ret = core(ft_strdup(node->p.cmd), exec_s->envp, exec_s, env);
			exit(ret);
		}
	}
	else
	{
		// printf("registring ctrl_c_handler PARENT\n");
		waitpid(pid, &status, 0);
		signal(SIGINT, enter);
		// signal(SIGINT, enter);
		// printf("enter1\n");
		if (WIFEXITED(status))
		{
			es = status;
			g_exec_struct->exit_status = es;
			return es;
		}
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)
				exec_s->exit_status |= ((128 + WTERMSIG(status)) << 8) & 0xff00;
			else if (WTERMSIG(status) == 3)
				printf("Quit: %d\n", WTERMSIG(status));
			else if (WTERMSIG(status) != 11)
				exec_s->exit_status |= ((128 + WTERMSIG(status)) << 8) & 0xff00;
		}
	}
	return 0;
}

void herdoc_handler(int p)
{
	(void)p;
	fflush(stdout);
	fflush(stderr);
	fflush(stdin);
	exit_status_fail();
	return;
}


void exit_herdoc(int p)
{
	(void)p;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit_status_fail();
	g_flag = 0;
}

char *get_next_line(int fd)
{
	char p[10000];

	int i = 0;
	while (read(fd, &p[i], 1) != 0)
	{
		if (p[i] == '\n')
			break;
		i++;
	}
	p[i] = 0;
	return ft_strdup(p);
}

void handle_herdoc_store_pipe(t_parsing_node *node, t_exec_struct *exec_s)
{
	int i;
	char *p;
	int pid;
	int status = 0;

	g_flag = 1;
	//signal(SIGINT, exit_herdoc);
	if (!it_has_herdoc(node))
		return;
	// Open a pipe
	// Keep reading until the last herdoc which is interesting
	// Open a pipe to use it as input for our program
	signal(SIGINT, SIG_IGN);
	pipe(node->fd);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		i = 0;
		while (node->reds.herdoc_array[i] && node->reds.herdoc_array[i + 1])
		{
			ft_putstr_fd("> ", 2);
			p = get_next_line(0);
			if (ft_strcmp(p, node->reds.herdoc_array[i]->herdoc_keyword) == 0)
				i++;
			free(p);
		}

		while (1)
		{
			ft_putstr_fd("> ", 2);
			p = get_next_line(0);
			if (p[0] == 0)
			{
				free(p);
				break;
			}
			if (ft_strcmp(p, node->reds.herdoc_array[i]->herdoc_keyword) == 0)
				break;
			if (!node->reds.herdoc_array[i]->is_quoted && ft_strchr(p, '$'))
				p = expand_an_array_having_dlr(p, exec_s);
			write(node->fd[1], p, ft_strlen(p));
			write(node->fd[1], "\n", 1);
			free(p);
		}
		close(node->fd[1]);
		exit(0);
	}
	else
	{
		wait(&status);
		signal(SIGINT, enter);
		close(node->fd[1]);
		if (WIFSIGNALED(status))
		{
			char c;
			write(1, "\n", 1);
			while(read(node->fd[0], &c, 1) == 1)
			;
			loop_handler(NULL, g_exec_struct);
			//close(node->fd[0]);
		}
	}
}

void traverse_for_herdoc(t_parsing_node *root, t_envp **env)
{
	if (root == NULL)
		return;
	traverse_for_herdoc(root->lchild, env);
	handle_herdoc_store_pipe(root, g_exec_struct);
	traverse_for_herdoc(root->rchild, env);
}

void execute(t_parsing_node *root, t_exec_struct *exec_s, t_envp **env)
{
	traverse_for_herdoc(root, env);
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
