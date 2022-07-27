
#include "minishell.h"

// 1 - empty paranthesis "()" "(())"
// 2 - Not balanced paranthesis "(()"
// 3 - before ( It should be just PIPE or AND or OR or at the start of the line.

int check_empty_para(t_lnode *head)
{
	t_lnode *current;

	current = head;
	while (get_token(current) != EOL)
	{
		if (get_token(current) == LEFT_PAR)
		{
			current = current->next;
			current = ignore_spaces_ret(current);
			if (get_token(current) == EOL)
				return (FAIL);
			if (get_token(current) == RIGHT_PAR)
				return (FAIL);
		}
		current = current->next;
	}
	return (SUCCESS);
}


int check_if_balanced(t_lnode *head)
{
	t_lnode *current;
	int     count;
	int     flag;

	current = head;
	count = 0;
	flag = SUCCESS;
	while (get_token(current) != EOL)
	{
		if (get_token(current) == LEFT_PAR)
			count++;
		else if (get_token(current) == RIGHT_PAR)
			count--;

		if (count < 0)
		{
			flag = FAIL;
			break;
		}
		current = current->next;
	}
	if (count != 0)
		flag = FAIL;
	return flag;
}

static t_lnode *return_lp(t_lnode *head)
{
	t_lnode *current;
	current = head;
	while (get_token(current) != EOL)
	{
		if (get_token(current) == LEFT_PAR)
			return (current);
		current = current->next;
	}
	return (NULL);
}



// static int check_right(t_lnode *head, t_lnode *lp)
// {
// 	e_token t;

// 	// it can be any valid one PIPE OR AND LEFT_P
// 	t = PIPE;
// 	while (head != lp)
// 	{
// 		if (get_token(head) != SPC)
// 			t = get_token(head);
// 		head = head->next;
// 	}
// 	if (t == PIPE || t == OR || t == AND || t == LEFT_PAR)
// 		return (SUCCESS);
// 	return (FAIL);
// }
static int check_left(t_lnode *head, t_lnode *lp)
{
	e_token t;

	// it can be any valid one PIPE OR AND LEFT_P
	t = PIPE;
	while (head != lp)
	{
		if (get_token(head) != SPC)
			t = get_token(head);
		head = head->next;
	}
	if (t == PIPE || t == OR || t == AND || t == LEFT_PAR)
		return (SUCCESS);
	return (FAIL);
}

int check_left_of_left_p(t_lnode *head)
{
	t_lnode *current;

	current = head;
	while (get_token(current) != EOL)
	{
		current = return_lp(current);
		if (current == NULL)
			break;
		if (check_left(head, current) == FAIL)
			return (FAIL);
		current = current->next;
	}
	return (SUCCESS);
}

int is_red(t_lnode *node)
{
	e_token t;

	t = node->type.token;
	return (t == DLMI || t == APPND || t == REDRI || t == REDRO);
}

int	check_right_part(t_lnode *head)
{
	t_lnode	*current;

	current = head;
	while (get_token(current) != EOL)
	{
		if (get_token(current) == RIGHT_PAR)
		{
			current = current->next;
			current = ignore_spaces_ret(current);

			if (get_token(current) == EOL)
				return SUCCESS;
			if (get_token(current) != PIPE
				&& get_token(current) != AND
				&& get_token(current) != OR
				&& get_token(current) != EOL
				&& get_token(current) != RIGHT_PAR
				&& !is_red(current))
					return(FAIL); 	
		}
		else
			current = current->next;
	}
	return(SUCCESS);
}
// ((ls -la) cat | grep H) |            (hhh)

int check_left_par(t_lnode *head)
{
	if (check_empty_para(head) == FAIL
	||	check_if_balanced(head) == FAIL
	||	check_left_of_left_p(head) == FAIL
	|| check_right_part(head) == FAIL)
		return FAIL;
	return SUCCESS;
}

