#include "minishell.h"
#include "exec.h"


void exec_and_or(t_parsing_node *root, t_exec_struct *exec_s, char **envp)
{
	execute(root->lchild, exec_s, envp);
	if (root->type == AND)
	{
		if (WIFEXITED(exec_s->exit_status) && WEXITSTATUS(exec_s->exit_status) == 0)1
			execute(root->rchild, exec_s, envp);
	}
	else
	{
		if (WIFEXITED(exec_s->exit_status) && WEXITSTATUS(exec_s->exit_status) != 0)
			execute(root->rchild, exec_s, envp);
	}
}


