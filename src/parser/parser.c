#include "minishell.h"

// This one g"re"p should be CMD -> EOL

int is_quote(t_lnode *node)
{
	return ((get_token(node) == DBLQT) || (get_token(node) == SGLQT));
}
void consolidate_commands(t_lnode **head)
{
	t_lnode *current;
	t_lnode *p;
	t_lnode *tmp;

	current = *head;
	while (get_token(current) != EOL)
	{
		if (get_token(current) == CMD && is_quote(current->next) && get_token(current->next->next) == CMD)
		{
			set_cmd(current->next->next, ft_strjoin(get_cmd(current), get_cmd(current->next->next), 1));
			tmp = current;
			if (current == *head)
				*head = current->next;
			else
				p->next = current->next;
			current = current->next;
			free_lexer_node(tmp);
		}
		p = current;
		current = current->next;
	}
}

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
	//log_(*head);
	expand_env_variables(head, exec_s);
	consolidate_commands(head);
	//fix_after_expansion(*head);
	log_(*head);
	root = parse_tree(*head);
    return root;
}