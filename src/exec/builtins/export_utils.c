#include "minishell.h"

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
	int t;

	curr = *env;
	t = 0;
	s = ft_strndup(str, ft_egale_len(str));
	printf("%s\n", s);
	// printf("%lu\n", ft_strlen(s) - 2);
	// printf("%lu\n", ft_strlen(s) - 1);
	// printf("%c\n", str[ft_strlen(s) - 2]);
	// printf("%c\n", str[ft_strlen(s) - 1]);
	while (curr)
	{
		if (!ft_strncmp(s, curr->str, ft_strlen(s) - 1) && s[ft_strlen(s) - 1] == '+')
		{
			t = 1;
			curr->str = ft_strjoin(curr->str, &ft_strchr(str, '=')[1], 0);
		}
		else if (!ft_strncmp(s, curr->str, ft_strlen(s)) && s[ft_strlen(s)] == '=')
		{
			t = 1;
			free(curr->str);
			curr->str = ft_strdup(str);
		}
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
		return (-1);
	else
		return (1);
}