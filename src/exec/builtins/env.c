
#include "minishell.h"

int ft_env(t_parsing_node *node, t_exec_struct *exec_s, t_envp **env)
{
	(void)exec_s;
	t_envp *head;
	t_envp	*current;
	char	*s;
	char	*var;
	int	i;
	int	flag;

	flag = 0;
	head = *env;
	if (node->cmd.argv[1] == NULL)
	{
		while(head)
		{
			if(ft_egale_len(head->str) != -1)
				fprintf(stdout,"%s\n", head->str);
			head = head->next;
		}
	}
	else
	{
		i = 1;
		while (node->cmd.argv[i])
		{
			if (ft_egale_len(node->cmd.argv[i]) != -1 && node->cmd.argv[i][0] != '=')
				s = ft_strndup(node->cmd.argv[i], ft_egale_len(node->cmd.argv[i]));
			else
			{
				fprintf(stderr, "No such file or directory\n");
				exit_status_fail();
				return(-1);
			}
			current = *env;
			while(current)
			{
				var = ft_strndup(current->str, ft_egale_len(current->str));
				if (!ft_strcmp(s, var) && current->str[ft_egale_len(current->str)] == '=')
				{
					flag = 1;
					free(current->str);
					current->str = ft_strdup(node->cmd.argv[i]);
				}
				free(var);
				current = current->next;
			}
			free(s);
			if (flag == 0)
				new_env(env, node->cmd.argv[i]);
			i++;	
		}
		while(head)
		{
			if(ft_egale_len(head->str) != -1)
				fprintf(stdout,"%s\n", head->str);
			head = head->next;
		} 
	}
	exit_status_success();
	return 0;
}