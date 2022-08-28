#include "minishell.h"

void	ft_unset_node(t_envp **env, char *arg)
{
	t_envp	*current;
	t_envp	*temp;
	t_envp	*next;
	int	i;

	i = 0;
	current = *env;
	if (!ft_strncmp(arg, (*env)->str, ft_strlen(arg)) && (*env)->str[ft_strlen(arg)] == '=')
	{
		temp = (*env)->next;
		free((*env)->str);
		free(*env);
		*env = temp;
	}
	else
	{
		current = *env;
		while(current->next)
		{
			if (current->next->next)
				next = current->next->next;
			else
				next = NULL;
			if (!ft_strncmp(arg, current->next->str, ft_strlen(arg))
				 && current->next->str[ft_strlen(arg)] == '=')
			{
				free(current->next->str);
				free(current->next);
				current->next = next;
				break ;
			}
			else if (!ft_strncmp(arg, current->next->str, ft_strlen(arg))
				&& current->next->str[ft_strlen(arg)] == '\0')
				{
					free(current->next->str);
					free(current->next);
					current->next = next;
					break ;
				}
			if (current->next != NULL)
			 	current = current->next;	
		}
	}
}

void	ft_unset(t_parsing_node *root, t_envp **env)
{
	int	i;

	if (!root->cmd.argv[1])
		perror("not enough arguments");
	else
	{
		i = 1;
		while(root->cmd.argv[i])
		{
			ft_unset_node(env, root->cmd.argv[i]);
			i++;
		}

	}
	exit_status_success();
	convert(*env);
}
	