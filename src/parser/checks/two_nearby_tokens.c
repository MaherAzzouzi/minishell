#include "minishell.h"

static int	check_redirections(t_lnode **current)
{
	if (get_token(*current) == REDRI
		|| get_token(*current) == REDRO
		|| get_token(*current) == DLMI
		|| get_token(*current) == APPND)
	{
		*current = (*current)->next;
		*current = ignore_spaces_ret(*current);
		if (get_token(*current) != SGLQT && get_token(*current) != DBLQT
			&& get_token(*current) != CMD && get_token(*current) != DLR)
			return (FAIL);
	}
	return (SUCCESS);
}

int	two_successive_pars(t_lnode	*head)
{
	t_lnode	*current;
	int		ret;

	current = head;
	while (get_token(current) != EOL)
	{
		ret = check_redirections(&current);
		if (ret == FAIL)
			return (ret);
		current = current->next;
	}
	return (SUCCESS);
}
