#include "minishell.h"
#include "lexer.h"
#include "parser.h"

#include <termios.h>
#include <unistd.h>

char *read_command_line(t_exec_struct *exec_struct)
{
	(void)exec_struct;
	char *cmd;
	char *cmd2;
	int i;

	// if (g_exec_struct->exit_status == 0)
	// 	cmd = readline(":)$ ");
	// else

	cmd = readline("$ ");
	if (!cmd)
	{
		if (g_exec_struct->exit_status == 256)
			exit(1);
		else
			exit(0);
	}

	add_history(cmd);
	i = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '\r'
	|| cmd[i] == '\n' || cmd[i] == '\f' || cmd[i] == '\v' )
		i++;
	cmd2 = ft_strdup(&cmd[i]);
	free(cmd);
	return (cmd2);
}

int core(char *cmd, char *envp[], t_exec_struct *exec_struct, t_envp **env)
{
	(void)envp;
	t_lnode *head;
	t_parsing_node *root;
	(void)envp;
	head = lex(cmd);
	root = parse(&head, exec_struct);
	if (root)
		execute(root, exec_struct, env);
	free_all(cmd, head, root);
	return (WEXITSTATUS(exec_struct->exit_status));
}

void ctrl_c_handler(int p)
{
	(void)p;
	write(1, "\n", 1);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	//exit(1);
	return;
}

void ctrl_b_handler(int p)
{
	printf("Quit: %d\n", p);

	return;
}

void enter(int p)
{
	(void)p;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit_status_fail();
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
	rl_catch_signals = 0;
	rl_outstream = stderr;
	
	signal(SIGINT,  enter);
	signal(SIGQUIT, ctrl_b_handler);
	g_exec_struct = &exec_struct;

	ft_memset(&exec_struct, 0, sizeof(exec_struct));

	setbuf(stdout, NULL);
	init(&exec_struct, envp);
	loop_handler(envp, &exec_struct);
}
