/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:28:10 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:28:52 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	spawn_process(t_spp *s)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, ctrl_c_handler);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		spawn_process_child(s);
	}
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

void	pipe_chain_exec_hoc(t_parsing_node *node, int *fd,
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

void	pipe_chain_exec_rc(t_parsing_node *node, int *fd,
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

int	exec_simple_cmd_builtin(t_parsing_node *node, t_exec_struct *exec_s,
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
