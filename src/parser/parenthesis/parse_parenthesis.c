#include "minishell.h"

t_lnode	*find_next_right_par_or_eol(t_lnode *start)
{
	while (1)
	{
		if (get_token(start) == RIGHT_PAR
			|| get_token(start) == EOL
			|| get_token(start) == AND
			|| get_token(start) == OR
			|| get_token(start) == PIPE)
			return (start);
		start = start->next;
	}
	return (NULL);
}

char	*get_only_parenthesis_content(t_lnode *open_p, t_lnode *closing_p)
{
	char	*p;

	p = ft_strndup(open_p->parenthesis_start + 1,
			closing_p->parenthesis_start - open_p->parenthesis_start - 1);
	return (p);
}

typedef struct s_p_p
{
	t_lnode			*current;
	int				count;
	char			*cmd;
	t_parsing_node	*node;
	t_lnode			*open_p;
	t_lnode			*closing_p;
	t_parsing_node	*n;
}	t_p_p;

static void	init_part(t_p_p *p, t_lnode *head)
{
	p->count = 0;
	p->current = head;
	p->cmd = ft_strdup("");
	p->node = alloc_node(CMD);
	p->closing_p = NULL;
}

static void	left_parent(t_p_p *p, t_lnode	*end)
{
	p->open_p = p->current;
	p->current = p->current->next;
	while (p->current != end)
	{
		if (get_token(p->current) == LEFT_PAR)
			p->count++;
		if (get_token(p->current) == RIGHT_PAR && p->count == 0)
			break ;
		else if (get_token(p->current) == RIGHT_PAR)
			p->count--;
		if (get_token(p->current) == CMD)
			p->cmd = ft_strjoin(p->cmd, get_cmd(p->current), 0);
		else
			p->cmd = ft_strjoin(p->cmd,
					convert_token(get_token(p->current)), 0);
		p->current = p->current->next;
	}
}

static t_parsing_node	*norm_shit(t_p_p *p)
{
	p->closing_p = p->current;
	p->n = parse_redirections(p->current->next,
			find_next_right_par_or_eol(p->current->next));
	free(p->cmd);
	p->cmd = get_only_parenthesis_content(p->open_p, p->closing_p);
	if (p->n == NULL)
	{
		p->node->p.parenthesised = 1;
		p->node->p.cmd = p->cmd;
		return (p->node);
	}
	else
	{
		free_node(p->node);
		p->n->p.cmd = p->cmd;
		p->n->p.parenthesised = 1;
		return (p->n);
	}
}

t_parsing_node	*parse_parenthesis(t_lnode *head, t_lnode *end)
{
	t_p_p	p;

	init_part(&p, head);
	while (p.current != end)
	{
		if (get_token(p.current) == LEFT_PAR)
		{
			left_parent(&p, end);
			if (get_token(p.current) == RIGHT_PAR && p.count == 0)
				break ;
		}
		p.current = p.current->next;
	}
	if (p.cmd[0] != 0)
		return (norm_shit(&p));
	else
	{
		free(p.cmd);
		free_node(p.node);
		return (NULL);
	}
}
