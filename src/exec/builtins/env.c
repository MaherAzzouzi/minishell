
#include "minishell.h"

int ft_env(t_parsing_node *node, t_exec_struct *exec_s, t_envp *env)
{
	(void)node;
	(void)exec_s;
	t_envp *head;

	head = env;
	while(head)
	{
		fprintf(stdout,"%s\n", head->str);
		head = head->next;
	}
	return 0;
	// int	i;


	// i = 0;
	// if (ft_strcmp(node->cmd.argv[0], "env") == 0 && node->cmd.argv[1] == NULL)
	// {
	// 	while(exec_s->envp[i])
	// 	{
	// 		printf("%s\n", exec_s->envp[i]);
	// 		i++;
	// 	}
	// 	return(SUCCESS);
	// }
	// else
	// {
	// 	printf("too many arguments\n");
	// 	return(FAIL);
	// }
}