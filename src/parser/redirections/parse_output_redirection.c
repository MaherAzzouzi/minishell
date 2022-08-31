#include "minishell.h"

t_parsing_node	*parse_output_redirection(t_lnode *head)
{
	t_parsing_node	*node;
	t_lnode			*o_red;

	node = alloc_node(CMD);
	o_red = find_o_red(head);
	head = ignore_spaces_ret(head);
	if (get_token(head) == CMD)
		node->reds.o_r_param = ft_strdup(get_cmd(head));
	else
		exit('<');
}
