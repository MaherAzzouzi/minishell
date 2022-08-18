
#include "minishell.h"

int ft_env(t_parsing_node *node, t_exec_struct *exec_s, t_envp **env)
{
	(void)node;
	(void)exec_s;
	t_envp *head;

	head = *env;
	while(head)
	{
		if(ft_egale_len(head->str) != -1)
			printf("%s\n", head->str);
		head = head->next;
	}
	exit_status_success();
	return 0;
}