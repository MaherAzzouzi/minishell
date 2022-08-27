#include "minishell.h"

int	is_end_before_start(t_lnode *start, t_lnode *end)
{
	while (end && get_token(end) != EOL)
	{
		if (end == start)
			return (1);
		end = end->next;
	}
	return (0);
}

t_lnode	*get_end(t_lnode *head)
{
	while (get_token(head) != EOL)
		head = head->next;
	return (head);
}

t_lnode	*return_highest_priv(t_lnode *current, t_lnode *end)
{
	t_lnode	*p;
	int		flag;
	int		count;

	p = get_end(current);
	flag = 0;
	count = 0;
	while (current != end && get_token(current) != EOL)
	{
		if (get_token(current) == LEFT_PAR)
			count++;
		if (get_token(current) == PIPE && get_token(p) != AND
			&& flag == 0 && count == 0 && get_token(p) != OR)
		{
			p = current;
			flag = 1;
		}
		else if ((get_token(current) == AND || get_token(current) == OR)
			&& count == 0)
			p = current;
		if (get_token(current) == RIGHT_PAR)
			count--;
		current = current->next;
	}
	return (p);
}

static t_lnode	*check_first_and_or(t_lnode	*current)
{
	while (get_token(current) != EOL)
	{
		if (get_token(current) == AND || get_token(current) == OR)
			return (current);
		current = current->next;
	}
	return (current);
}

t_lnode	*stop_at_higher_priv(t_lnode *highest)
{
	t_lnode	*current;

	current = highest;
	if (get_token(highest) == PIPE)
		return (check_first_and_or(current));
	else if (get_token(highest) == AND || get_token(highest) == OR)
	{
		current = current->next;
		while (get_token(current) != EOL)
		{
			if (get_token(current) == AND || get_token(current) == OR)
				return (current);
			current = current->next;
		}
		return (current);
	}
	else
		return (highest);
}

t_parsing_node	*recursive_tree_creation(t_lnode *start, t_lnode *end)
{
	t_parsing_node	*node;
	t_lnode			*highest;

	node = NULL;
	highest = return_highest_priv(start, end);
	if (get_token(highest) != EOL)
		node = alloc_node(get_token(highest));
	if (get_token(highest) != PIPE
		&& get_token(highest) != AND
		&& get_token(highest) != OR)
	{
		node = analyze_return_node(start, end);
		return (node);
	}
	node->lchild = recursive_tree_creation(start, highest);
	node->rchild = recursive_tree_creation(highest->next,
			stop_at_higher_priv(highest));
	return (node);
}

t_parsing_node	*parse_tree(t_lnode *head)
{
	t_parsing_node	*root;

	root = recursive_tree_creation(head, get_end(head));
	return (root);
}
