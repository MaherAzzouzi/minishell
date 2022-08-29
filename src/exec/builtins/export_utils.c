#include "minishell.h"

void	free_env(t_envp **head)
{
	t_envp	*curr;
	t_envp	*temp;

	curr = *head;
	while (curr)
	{
		temp = curr;
		if (curr->str)
			free(curr->str);
		curr = curr->next;
		free(temp);
	}
	*head = 0;
}

int	ft_isalnum2(int c)
{
	return ((c <= 'z' && c >= 'a')
		|| (c <= 'Z' && c >= 'A') || (c <= '9' && c >= '0'));
}

char	*ft_strndup(char *str, int j)
{
	char	*ret;
	int		i;

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

int	ft_check_var_syntx(char *str)
{
	int	i;

	i = 0;
	while (i < ft_egale_len(str) - 1)
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	set_ar_w_e_o_n(char **s, char *str)
{
	if (check_equal(str) == 2)
		*s = ft_strndup(str, ft_egale_len(str) - 1);
	else if (check_equal(str) == 3)
		*s = ft_strdup(str);
	else
		*s = ft_strndup(str, ft_egale_len(str));
}

void check_new_env_core(	t_envp	*curr, char *s, char *var, int t)
{
	if (!ft_strcmp(s, curr->str) && check_equal(str) == 1)
	{
		t = 1;
		free(curr->str);
		curr->str = ft_strdup(str);
	}
	else if (!ft_strcmp(s, curr->str))
		t = 1;
	else if (!ft_strcmp(s, var) && curr->str[ft_egale_len(curr->str)] == '='
		&& check_equal(str) == 2)
	{
		t = 1;
		curr->str = ft_strjoin(curr->str, &ft_strchr(str, '=')[1], 0);
	}
	else if (!ft_strcmp(s, var)
		&& curr->str[ft_egale_len(curr->str)] == '=')
	{
		t = 1;
		free(curr->str);
		curr->str = ft_strdup(str);
	}
}

typedef struct s_new_env
{
	t_envp	*curr;
	char	*s;
	char	*var;
	int		t;
} t_new_env;
static void	cor_()
		new.var = ft_strndup(new.curr->str, ft_egale_len(new.curr->str));
		if (!ft_strcmp(new.s, new.curr->str) && check_equal(str) == 1)
		{
			new.t = 1;
			free(new.curr->str);
			new.curr->str = ft_strdup(str);
		}
		else if (!ft_strcmp(new.s, new.curr->str))
			new.t = 1;
		else if (!ft_strcmp(new.s, new.var) && new.curr->str[ft_egale_len(new.curr->str)] == '='
			&& check_equal(str) == 2)
		{
			new.t = 1;
			new.curr->str = ft_strjoin(new.curr->str, &ft_strchr(str, '=')[1], 0);
		}
		else if (!ft_strcmp(new.s, new.var)
			&& new.curr->str[ft_egale_len(new.curr->str)] == '=')
		{
			new.t = 1;
			free(new.curr->str);
			new.curr->str = ft_strdup(str);
		}
		free(new.var);

int	check_new_env(char *str, t_envp **env)
{
	t_new_env	new;

	new.curr = *env;
	new.t = 0;
	set_ar_w_e_o_n(&new.s, str);

	while (new.curr)
	{
		new.curr = new.curr->next;
	}
	free(new.s);
	return (new.t);
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
	return (3);
}

int check_export_syntax(char *str)
{
	int i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 || (check_equal(str) == -1))
	{
		return (-1);
	}
	else
		return (1);
}