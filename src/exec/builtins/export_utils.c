#include "minishell.h"


int check_equal(char *str);
void    free_env(t_envp **head)
{
    t_envp  *curr;
    t_envp  *temp;

    curr = *head;
    while(curr)
    {
        temp = curr;
		if (curr->str)
        	free(curr->str);
        curr = curr->next;
        free(temp);
    }
    *head = 0;
}

int ft_isalnum2(int c)
{
	return ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A') || (c <= '9' && c >= '0'));
}

char *ft_strndup(char *str, int j)
{
	char *ret;
	int i;

	ret = malloc(sizeof(char) * j + 1);
	i = 0;
	while (i < j)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

int ft_check_var_syntx(char *str)
{
	int i;

	i = 0;
	while (i < ft_egale_len(str) - 1)
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int check_new_env(char *str, t_envp **env)
{
	t_envp *curr;
	char *s;
	char	*var;
	int t;

	curr = *env;
	t = 0;
	if (check_equal(str) == 2)
		s = ft_strndup(str, ft_egale_len(str) - 1);
	else
		s = ft_strndup(str, ft_egale_len(str));
	while (curr)
	{
		var = ft_strndup(curr->str, ft_egale_len(curr->str));
		if (!ft_strcmp(s, var) && curr->str[ft_egale_len(curr->str)] =='=' && check_equal(str) == 2)
		{
			t = 1;
			curr->str = ft_strjoin(curr->str, &ft_strchr(str, '=')[1], 0);
		}
		else if (!ft_strcmp(s, var) && curr->str[ft_egale_len(curr->str)] == '=')
		{
			t = 1;
			free(curr->str);
			curr->str = ft_strdup(str);
		}
		free(var);
		curr = curr->next;
	}
	free(s);
	return (t);
}

int check_equal(char *str)
{
	int i;
	int x;

	x = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			x = i;
			break;
		}
		i++;
	}
	if (x > 0)
	{
		if (ft_isalnum(str[x - 1]))
			return (1);
		else if (str[x - 1] == '+')
			return (2);
		else
			return (-1);
	}
	return (1);
	// if (ft_isalnum(str[x - 1]))
	// 	return(1);
	// else
	// 	return(-1);
}

int check_export_syntax(char *str)
{
	int i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 || (check_equal(str) == -1))
	{
		printf("[%d] love you honey\n", ft_isalpha(str[0]));
		return (-1);
	}
	else
		return (1);
}