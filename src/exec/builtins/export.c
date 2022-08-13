#include "minishell.h"
int	ft_egale_len(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '=')
			return(i);
		i++;
	}
	return(-1);
}

void	ft_sort_export(t_envp	*head)
{
	t_envp	*current;
	t_envp	*front;
	char	*temp;

	current = head;
	int i;

	i = 0;
	while(current)
	{
		front = current->next;
		while(front)
		{
			if (ft_strcmp(current->str, front->str) > 0)
			{
				temp = current->str;
				current->str = front->str;
				front->str = temp;
			}
			front = front->next;
		}
		current = current->next;
	}
}

void	p_(char *str, int len)
{
	int	i;

	i = 0;
	while(i <= len)
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\"");
	while(str[i])
	{
		printf("%c", str[i]);
		i++;
	}
	printf("\"");
	printf("\n");
}

void	ft_export(t_parsing_node *node, t_envp **env)
{
	t_envp  *export;
	t_envp  *current;
	(void)node;

	export = exxport(env);
	ft_sort_export(export);
	current = export;
	while(current)
	{
		printf("declare -x ");
		p_(current->str, ft_egale_len(current->str));
		current = current->next;
	}

}
