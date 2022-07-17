#include "minishell.h"
#include "exec.h"


void or_chain_exec(t_parsing_node *node, t_exec_struct *exec_s)
{
	if (node->type == OR)
	{
		// First we execute the command at the left.
        if (node->lchild->type == CMD)
			exec_simple_cmd(node->lchild, exec_s);
		else if (node->lchild->type == PIPE)
			pipe_chain_exec(node->lchild, exec_s);
		// We see if we should continue execution or no.
		// 0 means false here.
		if (WEXITSTATUS(exec_s->exit_status) == 0)
			return ;

		if (node->rchild->type == AND)
			and_chain_exec(node->rchild, exec_s);
		else if (node->rchild->type == OR)
			or_chain_exec(node->rchild, exec_s);
		else if (node->rchild->type == CMD)
			exec_simple_cmd(node->rchild, exec_s);
		else if (node->rchild->type == PIPE)
			pipe_chain_exec(node->rchild, exec_s);
	}
}

void and_chain_exec(t_parsing_node *node, t_exec_struct *exec_s)
{
	if (node->type == AND)
	{	
		printf("ITS OF TYPE %s\n", convert_token(node->lchild->type));
		// First we execute the command at the left.
        if (node->lchild->type == CMD)
			exec_simple_cmd(node->lchild, exec_s);
		else if (node->lchild->type == PIPE)
			pipe_chain_exec(node->lchild, exec_s);

		// We see if we should continue execution or no.
		// 0 means false here.
		if (WEXITSTATUS(exec_s->exit_status) != 0)
			return ;

		if (node->rchild->type == AND)
			and_chain_exec(node->rchild, exec_s);
		else if (node->rchild->type == OR)
			or_chain_exec(node->rchild, exec_s);
		else if (node->rchild->type == CMD)
			exec_simple_cmd(node->rchild, exec_s);
		else if (node->rchild->type == PIPE)
			pipe_chain_exec(node->rchild, exec_s);
	}
}