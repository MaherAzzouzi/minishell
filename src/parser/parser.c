#include "minishell.h"

t_parsing_node *parse(t_lnode *head)
{
    t_parsing_node *root;

	if (order_quotes(&head) == FAIL || check_all(head) == FAIL)
	{
		printf("Syntax Error!\n");
		return (NULL);
	}
	log_(head);
	root = parse_tree(head);
    return root;
}