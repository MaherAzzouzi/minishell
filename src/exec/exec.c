/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:33:18 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:33:20 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
