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

// replace a with b in string p.
void  replace(char *p, char a, char b)
{
	int i;

	i = 0;
	while (p[i])
	{
		if (p[i] == a)
			p[i] = b;
		i++;
	}
}

void replace_dlr_with_flag(t_lnode *head)
{
	t_lnode *current;

	current = head;
	while (get_token(current) != EOL)
	{
		if (get_token(current) == SGLQT)
		{
			current = current->next;
			while (get_token(current) != SGLQT)
			{
				if (get_token(current) == CMD)
				{
					if (!strchr(get_cmd(current), '\xff'))
						replace(get_cmd(current), '$', '\xff');
				}
				current = current->next;
			}
		}
		current = current->next;
	}
}

void flag_env_variables(t_lnode *head)
{
	while (get_token(head) != EOL)
	{
		if (get_token(head) == CMD && strchr(get_cmd(head), '$'))
		{
			int size = ft_strlen(head->type.cmd);
			char *p = (char *)malloc((size + 2) * sizeof(char));
			ft_memset(p, 0, size + 2);
			ft_memcpy(p, head->type.cmd, size);
			p[size] = '\xfe';
			free(head->type.cmd);
			head->type.cmd = p;
		}
		head = head->next;
	}
}

t_parsing_node *parse(t_lnode **head, t_exec_struct* exec_s)
{
    t_parsing_node *root;
	(void)exec_s;
	g_expand_node++;

	consolidate_dlr_with_cmd(head, exec_s);
	flag_env_variables(*head);
	if ((order_quotes(head) == FAIL || check_all(*head) == FAIL))
	{
		printf("Syntax Error!\n");
		return (NULL);
	}
	replace_dlr_with_flag(*head);
	// Here I should replace $ with \xff in case a cmd is between single quotes.
	join_quotes(*head);
	clean_empty_quote(head, SGLQT);
	clean_empty_quote(head, DBLQT);
	consolidate_commands(head);
	handle_wildcard(*head);
	log_(*head);
	root = parse_tree(*head);
	g_expand_node--;
    return root;
}