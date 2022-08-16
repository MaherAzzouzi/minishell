#include "minishell.h"

// void ctrl_b_handler(int p)
// {
// 	printf("Quit: %d\n", p);
// 	if (g_exec_struct->exit_status == 0)
// 		printf("\n" GREEN "$PWNAI> " WHITE);
// 	else
// 		printf("\n" RED "$PWNAI> " WHITE); 
// 	return;
// }

char *return_cmd_full_path(t_parsing_node *root, t_exec_struct *exec_s)
{
	char *p;

	if (root->cmd.cmd[0] != '/')
		p = check_if_bin_exist(root->cmd.cmd, exec_s->path);
	else
		p = root->cmd.cmd;
	return p;
}

pid_t spawn_process(int in, int out, t_parsing_node *root, t_exec_struct *exec_s, int *fd)
{
	pid_t pid;
	char *p;

	//printf("Executing %s\n", root->cmd.cmd);
	pid = fork();
	if (pid == 0)
	{
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
		printf("SETUP SIGNAL\n");
		if (root->p.parenthesised == 0)
		{
			p = return_cmd_full_path(root ,exec_s);
			if (p == NULL)
				show_errno();
			handle_herdoc_iredr(root, exec_s);
			handle_append_oredr(root);
			execve(p, root->cmd.argv, exec_s->envp);
			exit(0);
		}
		else
		{
			handle_herdoc_iredr(root, exec_s);
			handle_append_oredr(root);
			core(ft_strdup(root->p.cmd), exec_s->envp, exec_s);
			exit(0);
		}
	}
	else
	{
		// waitpid(-1, 0, 0);
		if (in != 0)
		{
			close(in);
		}
			// close(in);
		if (out != 1)
			close(out);
		return (pid);
	}
}

void pipe_chain_exec(t_parsing_node *node, t_exec_struct *exec_s)
{
	static int fd[2];
	int status;
	int pid2;
	int fd2;
	

	fd2 = dup(0);
	while (node->type == PIPE)
	{
		//printf("HERE1\n");
		int ret = pipe(fd);
		if (ret < 0)
			exit(-1);
		spawn_process(0, fd[1], node->lchild, exec_s, fd);
		if (node->rchild->type == CMD)
		{
			//printf("HERE IM PIPE\n");
			pid2 = spawn_process(fd[0], 1, node->rchild, exec_s, fd);
			waitpid(pid2, &status, 0);
			if (WIFEXITED(status))
			{
				exec_s->exit_status = status;
				//printf("Exit status is %d\n", WEXITSTATUS(status));
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
	while(waitpid(-1, &status, 0) != -1);
}


int	exec_simple_cmd(t_parsing_node *node, t_exec_struct *exec_s)
{
	pid_t	pid;
	char	*p;
	int		status;
	int		es;

	pid = fork();
	if (pid == 0)
	{
		printf("SETUP SIGNAL\n");
		if (node->p.parenthesised == 0)
		{
			p = return_cmd_full_path(node, exec_s);
			if (p == NULL)
				show_errno();
			handle_herdoc_iredr(node, exec_s);
			handle_append_oredr(node);
			//TODO: check if it's a directory or not.
			execve(p, node->cmd.argv, exec_s->envp);
			exit(0);
		}
		else
		{
			//printf("HANDLE PARANTHESIS!\n");
			handle_herdoc_iredr(node, exec_s);
			handle_append_oredr(node);
			int ret = core(ft_strdup(node->p.cmd), exec_s->envp, exec_s);
			exit(ret);
		}
	}
	else
	{	
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			es = status;
			exec_s->exit_status = es;
			//printf("Exit status is %d\n", WEXITSTATUS(es));
			return es;
		}
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) != 11)
			{
				printf("Quit: %d\n",WTERMSIG(status));
				exec_s->exit_status |= ((128 + WTERMSIG(status)) << 8) & 0xff00;
			}
		}
	}
	return 0;
}


void execute(t_parsing_node *root, t_exec_struct *exec_s, char *envp[])
{
	init(exec_s, envp);
	//builtins(root);

	////printf("LEFT-> %s\n", root->lchild->cmd.cmd);
	if (root->type == CMD)
		exec_simple_cmd(root, exec_s);
	else if (root->type == PIPE)
		pipe_chain_exec(root, exec_s);
	else if (root->type == OR)
		or_chain_exec(root, exec_s);
	else if (root->type == AND)
	{
		//printf("Executing AND\n");
		and_chain_exec(root, exec_s);
	}
}
