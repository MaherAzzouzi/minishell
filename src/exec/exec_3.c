/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:31:40 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 21:10:06 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_simple_cmd_core(char *p, struct stat *sb, t_parsing_node *node)
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
			ft_printf("minishell: %s: is a directory\n", node->cmd.cmd);
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

int	exec_simple_cmd_prt(pid_t pid)
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
			ft_printf("Quit: %d\n", WTERMSIG(status));
		else if (WTERMSIG(status) != 11)
			g_exec_struct->exit_status |= ((128 + WTERMSIG(status)) << 8)
				& 0xff00;
	}
	return (0);
}

void	exec_simple_cmd_child(t_parsing_node *node, t_envp **env)
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
