#include "minishell.h"

int	it_contain_only(char *p, char c)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (p[i] != c)
			return (0);
		i++;
	}
	return (1);
}

static void	writing_args(t_parsing_node *root)
{
	int	j;

	j = 1;
	while (root->cmd.argv[j])
	{
		if (root->cmd.argv[j + 1] == NULL)
			printf("%s", root->cmd.argv[j]);
		else
			printf("%s ", root->cmd.argv[j]);
		j++;
	}
	write(1, "\n", 2);
}

static void	check_n_arg(t_parsing_node *root, int *i)
{
	int	flag;

	flag = 1;
	while (flag)
	{
		if (root->cmd.argv[(*i)] && root->cmd.argv[(*i)][0]
				== '-' && it_contain_only(&root->cmd.argv[(*i)][1], 'n'))
			(*i)++;
		else
			flag = 0;
	}
}

void	ft_echo(t_parsing_node *root)
{
	int	i;

	i = 2;
	if (root->cmd.argv[1] == NULL)
		write(1, "\n", 2);
	else if (!(ft_strcmp(root->cmd.argv[1], "-n")))
	{
		while (root->cmd.argv[i])
		{
			check_n_arg(root, &i);
			if (root->cmd.argv[i] != NULL)
			{
				if (root->cmd.argv[i + 1] == NULL)
					printf("%s", root->cmd.argv[i]);
				else
					printf("%s ", root->cmd.argv[i]);
			}
			else
				break ;
			i++;
		}
	}
	else
		writing_args(root);
	exit_status_success();
}
