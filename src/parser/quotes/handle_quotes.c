#include "minishell.h"

int order_quotes(t_lnode **head)
{
	t_lnode * current;

	current = *head;
	while (current)
	{
		if (get_token(current) == SGLQT)
		{
			current = handle_single_quote(current);
			if (current == (t_lnode *)-1)
				return FAIL;

		}
		else if (get_token(current) == DBLQT)
		{
			current = handle_double_quote(current);
			if (current == (t_lnode *)-1)
				return FAIL;
		} else
			current = current->next;
	}
	return (SUCCESS);
}