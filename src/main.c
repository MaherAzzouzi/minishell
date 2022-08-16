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

int core(char *cmd, char *envp[], t_exec_struct *exec_struct)
{
	t_lnode	*head;
	t_parsing_node *root;
	head = lex(cmd);
	root = parse(&head, exec_struct);
	if (root)
		execute(root, exec_struct, envp);
	free_all(cmd, head, root);
	return (WEXITSTATUS(exec_struct->exit_status));
}

t_exec_struct *g_exec_struct;
char **g_envp;

int	main(int argc, char *argv[], char *envp[]);
void loop_handler(char *envp[], t_exec_struct* exec_s);

void ctrl_c_handler(int p)
{
	(void)p;
	if (g_exec_struct->exit_status == 0)
		printf("\n" GREEN "$PWNAI> " WHITE);
	else
		printf("\n" RED "$PWNAI> " WHITE); 
}

void loop_handler(char *envp[], t_exec_struct* exec_s)
{
	while (INFINIT)
	{
		char *cmd = read_command_line(exec_s);
		core(cmd, envp, exec_s);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	t_exec_struct exec_struct;
	signal(SIGINT, ctrl_c_handler);

	g_exec_struct = &exec_struct;
	g_envp = envp;

	ft_memset(&exec_struct, 0, sizeof(exec_struct));

	setbuf(stdout, NULL);
	init(&exec_struct, envp);
	loop_handler(envp, &exec_struct);
}
