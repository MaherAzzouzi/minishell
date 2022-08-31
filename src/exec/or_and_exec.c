#include "minishell.h"
#include "exec.h"

void	or_chain_exec(t_parsing_node *node, t_exec_struct *exec_s, t_envp *env)
{
	if (node->type == OR)
	{
		if (node->lchild->type == CMD)
			exec_simple_cmd(node->lchild, exec_s, &env);
		else if (node->lchild->type == PIPE)
			pipe_chain_exec(node->lchild, exec_s, &env);
		if (node->lchild->type == AND)
			and_chain_exec(node->lchild, exec_s, env);
		else if (node->lchild->type == OR)
			or_chain_exec(node->lchild, exec_s, env);
		if (WEXITSTATUS(exec_s->exit_status) == 0)
			return ;
		if (node->rchild->type == AND)
			and_chain_exec(node->rchild, exec_s, env);
		else if (node->rchild->type == OR)
			or_chain_exec(node->rchild, exec_s, env);
		else if (node->rchild->type == CMD)
			exec_simple_cmd(node->rchild, exec_s, &env);
		else if (node->rchild->type == PIPE)
			pipe_chain_exec(node->rchild, exec_s, &env);
	}
}

void	and_chain_exec(t_parsing_node *node, t_exec_struct *exec_s, t_envp *env)
{
	if (node->type == AND)
	{
		if (node->lchild->type == CMD)
			exec_simple_cmd(node->lchild, exec_s, &env);
		else if (node->lchild->type == PIPE)
			pipe_chain_exec(node->lchild, exec_s, &env);
		else if (node->lchild->type == AND)
			and_chain_exec(node->lchild, exec_s, env);
		else if (node->lchild->type == OR)
			or_chain_exec(node->lchild, exec_s, env);
		if (WEXITSTATUS(exec_s->exit_status) != 0)
			return ;
		if (node->rchild->type == AND)
			and_chain_exec(node->rchild, exec_s, env);
		else if (node->rchild->type == OR)
			or_chain_exec(node->rchild, exec_s, env);
		else if (node->rchild->type == CMD)
			exec_simple_cmd(node->rchild, exec_s, &env);
		else if (node->rchild->type == PIPE)
			pipe_chain_exec(node->rchild, exec_s, &env);
	}
}
