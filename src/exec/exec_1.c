/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:26:32 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 21:10:06 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	spawn_process_builtins(t_spp *s)
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

void	spawn_process_sc(t_spp *s, char *p, struct stat *sb)
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
			ft_printf("minishell: %s: is a directory\n", p);
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

void	spawn_process_handle_io(t_spp *s)
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

void	spawn_process_child(t_spp *s)
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
