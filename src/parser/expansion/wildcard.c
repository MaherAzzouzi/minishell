/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:51:01 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 22:48:12 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**n_is_matching(char *pattern, int n, int m)
{
	int	**lookup;
	int	i;
	int	j;

	lookup = (int **)malloc((n + 1) * sizeof(int *));
	memset(lookup, 0, (n + 1) * sizeof(int *));
	i = 0;
	while (i <= n)
	{
		lookup[i] = (int *)malloc((m + 1) * sizeof(int));
		memset(lookup[i], 0, (m + 1) * sizeof(int));
		i++;
	}
	lookup[0][0] = TRUE;
	j = 1;
	while (j <= m)
	{
		if (pattern[j - 1] == '*')
			lookup[0][j] = lookup[0][j - 1];
		j++;
	}
	return (lookup);
}

static int	is_matching_free(int **lookup, int n, int m)
{
	int	ret;
	int	i;

	ret = lookup[n][m];
	i = 0;
	while (i <= n)
		free(lookup[i++]);
	free(lookup);
	return (ret);
}

int	is_matching(char *str, char *pattern, int n, int m)
{
	int	i;
	int	j;
	int	**lookup;

	if (n == 0 && m == 0)
		return (TRUE);
	lookup = n_is_matching(pattern, n, m);
	i = 1;
	while (i <= n)
	{
		j = 1;
		while (j <= m)
		{
			if (pattern[j - 1] == '*')
				lookup[i][j] = lookup[i - 1][j] | lookup[i][j - 1];
			else if (pattern[j - 1] == str[i - 1])
				lookup[i][j] = lookup[i - 1][j - 1];
			else
				lookup[i][j] = FALSE;
			j++;
		}
		i++;
	}
	return (is_matching_free(lookup, n, m));
}

char	*open_current_dir(char *pattern)
{
	DIR				*d;
	struct dirent	*content;
	char			*p;

	p = ft_strdup("");
	d = opendir(".");
	while (1)
	{
		content = readdir(d);
		if (content == NULL)
			break ;
		if (content->d_name[0] != '.'
			&& is_matching(content->d_name, pattern,
				ft_strlen(content->d_name), ft_strlen(pattern)))
		{
			p = ft_strjoin(p, content->d_name, 0);
			p = ft_strjoin(p, " ", 0);
		}
	}
	closedir(d);
	p[ft_strlen(p) - 1] = 0;
	return (p);
}

void	handle_wildcard(t_lnode *head)
{
	t_token	t;
	t_lnode	*current;
	char	*tmp;
	char	*p;

	current = head;
	t = EOL;
	while (get_token(current) != EOL)
	{
		if (t != SGLQT && t != DBLQT
			&& get_token(current) == CMD
			&& ft_strchr(get_cmd(current), '*'))
		{
			tmp = get_cmd(current);
			p = open_current_dir(get_cmd(current));
			if (p[0] != 0)
			{
				set_cmd(current, p);
				free(tmp);
			}
		}
		t = get_token(current);
		current = current->next;
	}
}
