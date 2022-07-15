#include "minishell.h"
#include "exec.h"


void or_chain_exec(t_parsing_node *node, t_exec_struct *exec_s)
{
	static int fd[2];
	int status;
	int pid2;
	int fd2;
	

	while (node->type == OR)
	{
        
		node = node->rchild;
	}
}
