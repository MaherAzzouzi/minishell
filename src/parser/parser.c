#include "minishell.h"

t_parsing_node *parse(t_lnode **head, t_exec_struct* exec_s)
{
    t_parsing_node *root;

	if (order_quotes(head) == FAIL || check_all(*head) == FAIL)
	{
		printf("Syntax Error!\n");
		return (NULL);
	}
	clean_empty_quote(head, SGLQT);
	clean_empty_quote(head, DBLQT);
	log_(*head);
	expand_env_variables(head, exec_s);
	log_(*head);
	root = parse_tree(*head);
    return root;
}