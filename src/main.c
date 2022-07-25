#include "minishell.h"
#include "lexer.h"
#include "parser.h"

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
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	t_exec_struct exec_struct;

	ft_memset(&exec_struct, 0, sizeof(exec_struct));

	setbuf(stdout, NULL);
	init(&exec_struct, envp);

	while (INFINIT)
	{
		char *cmd = read_command_line(&exec_struct);
		core(cmd, envp, &exec_struct);
	}
}
