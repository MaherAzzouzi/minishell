#include "minishell.h"

char	*return_cmd_full_path(t_parsing_node *root, t_exec_struct *exec_s)
{
	char	*p;

	p = NULL;
	p = root->cmd.cmd;
	if (root->cmd.cmd[0] == '.' && root->cmd.cmd[1] == '/')
	{
		p = getcwd(NULL, 0);
		p = ft_strjoin(p, &root->cmd.cmd[1], 0);
	}
	else if (root->cmd.cmd[0] != '/' && root->cmd.cmd[0] != '.')
		p = check_if_bin_exist(root->cmd.cmd, exec_s->path);
	return (p);
}
/////// spawn_process

typedef struct s_sp_params
{
	int				in;
	int				out;
	t_parsing_node	*root;
	t_exec_struct	*exec_s;
	int				*fd;
	t_envp			**env;
}	t_spp;

static void	spawn_process_builtins(t_spp *s)
{
	int	stdout_;
	int	stdin_;

	stdout_ = dup(1);
	stdin_ = dup(0);
	if (is_builtin(s->root))
	{
		if (s->in != 0)
		{
			dup2(s->in, 0);
			close(s->in);
		}
		if (s->out != 1)
		{
			dup2(s->out, 1);
			close(s->out);
		}
		handle_append_oredr(s->root);
		handle_herdoc_iredr(s->root, s->exec_s);
		expand_one_node(s->root, s->exec_s);
		builtins(s->root, s->exec_s, s->env);
		dup2(stdout_, 1);
		dup2(stdin_, 0);
		exit(0);
	}
}

static void	spawn_process_sc(t_spp *s, char *p, struct stat *sb)
{
	if (s->root->cmd.cmd[0] != 0)
	{
		expand_one_node(s->root, s->exec_s);
		p = return_cmd_full_path(s->root, s->exec_s);
		if (p == NULL)
			show_errno(s->root->cmd.cmd);
		if (stat(p, sb) < 0)
			show_errno(p);
		if (S_ISDIR(sb->st_mode))
		{
			printf("minishell: %s: is a directory\n", p);
			exit(-2);
		}
	}
	handle_append_oredr(s->root);
	handle_herdoc_iredr(s->root, s->exec_s);
	if (s->root->cmd.cmd[0] == 0)
	{
		p = "/";
		s->root->cmd.argv[0] = "/";
	}
	execve(p, s->root->cmd.argv, s->exec_s->envp);
	exit(0);
}

static void	spawn_process_handle_io(t_spp *s)
{
	if (s->in != 0)
	{
		dup2(s->in, 0);
		close(s->in);
	}
	if (s->out != 1)
	{
		dup2(s->out, 1);
		close(s->out);
	}
	close(s->fd[0]);
	close(s->fd[1]);
}

static void	spawn_process_child(t_spp *s)
{
	char		*p;
	struct stat	sb;
	int			ret;

	spawn_process_builtins(s);
	spawn_process_handle_io(s);
	if (it_has_herdoc(s->root))
	{
		dup2(s->root->fd[0], 0);
		close(s->root->fd[0]);
	}
	if (s->root->p.parenthesised == 0)
	{
		p = NULL;
		spawn_process_sc(s, p, &sb);
	}
	else
	{
		handle_append_oredr(s->root);
		handle_herdoc_iredr(s->root, s->exec_s);
		ret = core(ft_strdup(s->root->p.cmd),
				s->exec_s->envp, s->exec_s, s->env);
		exit(ret);
	}
}

pid_t	spawn_process(t_spp *s)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, ctrl_c_handler);
	if (pid == 0)
		spawn_process_child(s);
	else
	{
		if (s->in != 0)
			close(s->in);
		if (s->out != 1)
			close(s->out);
		return (pid);
	}
	return (0);
}
/////// pipe chain exec

static void	pipe_chain_exec_hoc(t_parsing_node *node, int *fd,
								t_exec_struct *exec_s, t_envp **env)
{
	t_spp	s;

	if (it_has_herdoc(node->lchild))
	{
		close(fd[0]);
		fd[0] = node->lchild->fd[0];
	}
	else
	{
		s.env = env;
		s.exec_s = exec_s;
		s.fd = fd;
		s.in = 0;
		s.out = fd[1];
		s.root = node->lchild;
		spawn_process(&s);
	}
}

static void	pipe_chain_exec_rc(t_parsing_node *node, int *fd,
		t_exec_struct *exec_s, t_envp **env)
{
	t_spp	s;
	int		status;
	int		pid2;

	if (it_has_herdoc(node->rchild))
	{
		close(fd[0]);
		fd[0] = node->rchild->fd[0];
	}
	s.env = env;
	s.exec_s = exec_s;
	s.fd = fd;
	s.in = fd[0];
	s.out = 1;
	s.root = node->rchild;
	pid2 = spawn_process(&s);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		exec_s->exit_status = status;
}

void	pipe_chain_exec(t_parsing_node *node,
			t_exec_struct *exec_s, t_envp **env)
{
	static int	fd[2];
	int			fd2;
	int			status;

	fd2 = dup(0);
	while (node->type == PIPE)
	{
		pipe(fd);
		pipe_chain_exec_hoc(node, fd, exec_s, env);
		if (node->rchild->type == CMD)
			pipe_chain_exec_rc(node, fd, exec_s, env);
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
	signal(SIGINT, enter);
}
////// exec_simple_cmd

static int	exec_simple_cmd_builtin(t_parsing_node *node, t_exec_struct *exec_s,
				t_envp **env)
{
	int	stdout_;
	int	stdin_;

	stdout_ = dup(1);
	stdin_ = dup(0);
	handle_append_oredr(node);
	handle_herdoc_iredr(node, exec_s);
	expand_one_node(node, exec_s);
	builtins(node, exec_s, env);
	dup2(stdout_, 1);
	dup2(stdin_, 0);
	return (0);
}

static void	exec_simple_cmd_core(char *p, struct stat *sb, t_parsing_node *node)
{
	p = NULL;
	if (node->cmd.cmd[0] != 0)
	{
		expand_one_node(node, g_exec_struct);
		p = return_cmd_full_path(node, g_exec_struct);
		if (p == NULL)
			show_errno(node->cmd.cmd);
		if (stat(p, sb) < 0)
			show_errno(p);
		if (S_ISDIR(sb->st_mode))
		{
			printf("minishell: %s: is a directory\n", node->cmd.cmd);
			exit(-2);
		}
		if (access(p, X_OK) != 0)
			show_errno(node->cmd.cmd);
	}
	handle_append_oredr(node);
	handle_herdoc_iredr(node, g_exec_struct);
	if (node->cmd.cmd[0] == 0)
	{
		p = "/";
		node->cmd.argv[0] = "/";
	}
	execve(p, node->cmd.argv, g_exec_struct->envp);
}

static int	exec_simple_cmd_prt(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	signal(SIGINT, enter);
	if (WIFEXITED(status))
	{
		g_exec_struct->exit_status = status;
		return (status);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			g_exec_struct->exit_status |= ((128 + WTERMSIG(status)) << 8)
				& 0xff00;
		else if (WTERMSIG(status) == 3)
			printf("Quit: %d\n", WTERMSIG(status));
		else if (WTERMSIG(status) != 11)
			g_exec_struct->exit_status |= ((128 + WTERMSIG(status)) << 8)
				& 0xff00;
	}
	return (0);
}

static void	exec_simple_cmd_child(t_parsing_node *node, t_envp **env)
{
	struct stat	sb;
	char		*p;
	int			ret;

	if (it_has_herdoc(node))
	{
		dup2(node->fd[0], 0);
		close(node->fd[0]);
	}
	if (node->p.parenthesised == 0)
	{
		p = NULL;
		exec_simple_cmd_core(p, &sb, node);
		exit(0);
	}
	else
	{
		handle_append_oredr(node);
		handle_herdoc_iredr(node, g_exec_struct);
		ret = core(ft_strdup(node->p.cmd), g_exec_struct->envp,
				g_exec_struct, env);
		exit (ret);
	}
}

int	exec_simple_cmd(t_parsing_node *node, t_exec_struct *exec_s, t_envp **env)
{
	pid_t	pid;

	if (is_builtin(node))
		return (exec_simple_cmd_builtin(node, exec_s, env));
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, ctrl_c_handler);
	pid = fork();
	if (pid == 0)
		exec_simple_cmd_child(node, env);
	else
		return (exec_simple_cmd_prt(pid));
	return (0);
}

char	*get_next_line(int fd)
{
	char	p[10000];
	int		i;

	i = 0;
	while (read(fd, &p[i], 1) != 0)
	{
		if (p[i] == '\n')
			break ;
		i++;
	}
	p[i] = 0;
	return (ft_strdup(p));
}
/////////// handle_herdoc_store_pipe

static void	handle_herdoc_parent(t_parsing_node *node)
{
	int		status;
	char	c;

	wait(&status);
	signal(SIGINT, enter);
	close(node->fd[1]);
	if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		while (read(node->fd[0], &c, 1) == 1)
			;
		loop_handler(NULL, g_exec_struct);
	}
}

static void	herdoc_fill_pipe(t_parsing_node *node, int *i,
			t_exec_struct *exec_s)
{
	char	*p;

	while (1)
	{
		ft_putstr_fd("> ", 2);
		p = get_next_line(0);
		if (p[0] == 0)
		{
			free(p);
			break ;
		}
		if (ft_strcmp(p, node->reds.herdoc_array[*i]->herdoc_keyword) == 0)
			break ;
		if (!node->reds.herdoc_array[*i]->is_quoted && ft_strchr(p, '$'))
			p = expand_an_array_having_dlr(p, exec_s);
		write(node->fd[1], p, ft_strlen(p));
		write(node->fd[1], "\n", 1);
		free(p);
	}
}

void	handle_herdoc_store_pipe(t_parsing_node *node, t_exec_struct *exec_s)
{
	int		i;
	char	*p;

	if (!it_has_herdoc(node))
		return ;
	signal(SIGINT, SIG_IGN);
	pipe(node->fd);
	if (fork() == 0)
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
		herdoc_fill_pipe(node, &i, exec_s);
		close(node->fd[1]);
		exit(0);
	}
	else
		handle_herdoc_parent(node);
}

void	traverse_for_herdoc(t_parsing_node *root, t_envp **env)
{
	if (root == NULL)
		return ;
	traverse_for_herdoc(root->lchild, env);
	handle_herdoc_store_pipe(root, g_exec_struct);
	traverse_for_herdoc(root->rchild, env);
}

void	execute(t_parsing_node *root, t_exec_struct *exec_s, t_envp **env)
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
