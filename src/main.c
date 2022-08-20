#include "minishell.h"
#include "lexer.h"
#include "parser.h"

#include <termios.h>
#include <unistd.h>

char *read_command_line(t_exec_struct *exec_struct)
{
	char *cmd;
	if (exec_struct->exit_status == 0)
		cmd = readline(GREEN "$PWNAI> " WHITE);
	else
		cmd = readline(RED "$PWNAI> " WHITE);
	add_history(cmd);
	return (cmd);
}

int core(char *cmd, char *envp[], t_exec_struct *exec_struct, t_envp **env)
{
	t_lnode *head;
	t_parsing_node *root;
	head = lex(cmd);
	root = parse(&head, exec_struct);
	if (root)
		execute(root, exec_struct, envp, env);
	free_all(cmd, head, root);
	return (WEXITSTATUS(exec_struct->exit_status));
}

void ctrl_b_ignore(int p)
{
	(void)p;
	return;
}

void ctrl_b_handler(int p)
{
	printf("Quit: %d\n", p);
	if (g_exec_struct->exit_status == 0)
		printf("\n" GREEN "$PWNAI> " WHITE);
	else
		printf("\n" RED "$PWNAI> " WHITE);
	return;
}

void loop_handler(char *envp[], t_exec_struct *exec_s)
{
	t_envp *env;

	env = ennv(exec_s);
	while (INFINIT)
	{
		char *cmd = read_command_line(exec_s);
		if (!cmd)
			exit(1);
		core(cmd, envp, exec_s, &env);
	}
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	t_exec_struct exec_struct;
	
	// 

	rl_catch_signals = 0;

	// signal(SIGINT,  ctrl_c_handler);
	signal(SIGQUIT, ctrl_b_ignore);
	g_exec_struct = &exec_struct;

	ft_memset(&exec_struct, 0, sizeof(exec_struct));

	setbuf(stdout, NULL);
	init(&exec_struct, envp);
	loop_handler(envp, &exec_struct);
}
