#include "minishell.h"


int check_equal(char    *str)
{
	int i;
	int x;

	x = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == '=')
		{
			x = i;
			break ;
		}
		i++;
	}
	if(x > 0)
	{
		if (ft_isalnum(str[x - 1]))
			return(1);
		else
			return(-1);
	}
	else
		return(2);
}

int check_export_syntax(char	*str)
{
	int i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 || (check_equal(str) == -1))
		return(-1);
	if (check_equal(str) == 2)
		return(2);
	else
		return(1);
}