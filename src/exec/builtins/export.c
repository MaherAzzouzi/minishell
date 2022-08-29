#include "minishell.h"

int	ft_egale_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_sort_export(t_envp *head)
{
	t_envp	*current;
	t_envp	*front;
	char	*temp;
	int		i;

	i = 0;
	current = head;
	while (current)
	{
		front = current->next;
		while (front)
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

static void	print_exp(int len, char *str, int *i)
{
	printf("declare -x ");
	while ((*i) <= len)
	{
		printf("%c", str[(*i)]);
		(*i)++;
	}
	printf("\"");
	while (str[(*i)])
	{
		printf("%c", str[(*i)]);
		(*i)++;
	}
	printf("\"");
	printf("\n");
}

void	p_(char *str, int len)
{
	int	i;

	i = 0;
	if (len != -1)
		print_exp(len, str, &i);
	else
	{
		printf("declare -x ");
		while (str[i])
		{
			printf("%c", str[i]);
			i++;
		}
		printf("\n");
	}
}

static int	checking_new_env(t_parsing_node *node, t_envp **env, t_envp *export)
{
	int	i;
	int	t;

	i = 1;
	while (node->cmd.argv[i])
	{
		t = check_new_env(node->cmd.argv[i], env);
		if (check_export_syntax(node->cmd.argv[i]) == -1
			|| ft_check_var_syntx(node->cmd.argv[i]) == 0)
		{
			free_env(&export);
			ft_putstr_fd("not a valid identifier\n", 2);
			return (FAIL);
		}
		else if (check_export_syntax(node->cmd.argv[i]) == 1 && t == 0)
			new_env(env, node->cmd.argv[i]);
		i++;
	}
	return (SUCCESS);
}

int	ft_export(t_parsing_node *node, t_envp **env)
{
	t_envp	*export;
	t_envp	*current;

	export = exxport(env);
	ft_sort_export(export);
	current = export;
	if (node->cmd.argv[1] == NULL)
	{
		while (current)
		{
			p_(current->str, ft_egale_len(current->str));
			current = current->next;
		}
	}
	else
	{
		if (checking_new_env(node, env, export) == FAIL)
			return (FAIL);
	}
	free_env(&export);
	convert(*env);
	exit_status_success();
	return (SUCCESS);
}
