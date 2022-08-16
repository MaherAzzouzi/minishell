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
	write(1, "HH", 2);
	//loop_handler(g_envp, g_exec_struct);
	return;
}

void loop_handler(char *envp[], t_exec_struct* exec_s)
{
	while (INFINIT)
	{
		char *cmd = read_command_line(exec_s);
		core(cmd, envp, exec_s);
	}
}

struct termios ts;

void reset_the_terminal()
{
	tcsetattr(0, 0, &ts);
}

void handle_the_stuff(int num)
{
char buff[4];
buff[0] = '[';
buff[2] = '0' + num%10;
num /= 10;
buff[1] = '0' + num%10;
buff[3] = ']';
write(0, buff, sizeof buff);
}


int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	t_exec_struct exec_struct;
	int ret;
	
	struct termios tn;
	rl_catch_signals = 0;

	ret = tcgetattr(0, &ts);
	if (ret) {printf("ERROR!");}

	atexit(reset_the_terminal);
	tn = ts;

	tn.c_lflag &= ~ECHOCTL;

	ret = tcsetattr(0, 0, &tn);
	if (ret) {printf("ERROR!");}
	signal(SIGINT, ctrl_c_handler);

	printf("(pseudoshell)Start typing:\n" );
//while(1) {getc(stdin);}
//	exit (0);
	g_exec_struct = &exec_struct;
	g_envp = envp;

	ft_memset(&exec_struct, 0, sizeof(exec_struct));

	setbuf(stdout, NULL);
	init(&exec_struct, envp);
	loop_handler(envp, &exec_struct);
}
