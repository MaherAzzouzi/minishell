#include "minishell.h"

int	is_input_redirected(t_parsing_node *node)
{
	if (node->reds.i_r_params && node->reds.i_r_params[0])
		return (1);
	return (0);
}

int	is_output_redirected(t_parsing_node *node)
{
	if (node->reds.o_r_params && node->reds.o_r_params[0])
		return (1);
	return (0);
}

int	it_has_herdoc(t_parsing_node *node)
{
	if (node->reds.herdoc_array && node->reds.herdoc_array[0])
		return (1);
	return (0);
}

int	it_has_append(t_parsing_node *node)
{
	if (node->reds.append_array && node->reds.append_array[0])
		return (1);
	return (0);
}

int	handle_output_redirect(t_parsing_node *node)
{
	int	i;
	int	fd;

	if (!is_output_redirected(node))
		return (-1);
	i = 0;
	while (node->reds.o_r_params[i] && node->reds.o_r_params[i + 1] != NULL)
	{
		fd = open(node->reds.o_r_params[i], O_CREAT, 0664);
		if (fd < 0)
			exit(-1);
		i++;
	}
	fd = open(node->reds.o_r_params[i], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd < 0)
		exit(-1);
	return (fd);
}

// Now append >>

int	handle_append(t_parsing_node *node)
{
	int	i;
	int	fd;

	if (!it_has_append(node))
		return (-1);
	i = 0;
	while (node->reds.append_array[i] && node->reds.append_array[i + 1])
	{
		fd = open(node->reds.append_array[i], O_CREAT, 0664);
		if (fd < 0)
			exit(-1);
		i++;
	}
	fd = open(node->reds.append_array[i], O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (fd < 0)
		exit(-1);
	return (fd);
}

int	handle_append_oredr(t_parsing_node *node)
{
	int	out;

	out = -1;
	if (node->last_out_token == EOL)
		return (0);
	else if (node->last_out_token == REDRO)
	{
		out = handle_output_redirect(node);
		handle_append(node);
	}
	else if (node->last_out_token == APPND)
	{
		out = handle_append(node);
		handle_output_redirect(node);
	}	
	dup2(out, 1);
	close(out);
	return (0);
}

int	handle_input_redirect(t_parsing_node *node)
{
	int	i;
	int	fd;

	if (!is_input_redirected(node))
		return (-1);
	i = 0;
	while (node->reds.i_r_params[i] && node->reds.i_r_params[i + 1] != NULL)
	{
		fd = open(node->reds.i_r_params[i], O_CREAT, 0664);
		if (fd < 0)
			exit(-1);
		i++;
	}
	if (access(node->reds.i_r_params[i], R_OK) != 0)
		show_errno(node->reds.i_r_params[i]);
	fd = open(node->reds.i_r_params[i], O_RDONLY, 0664);
	if (fd < 0)
		exit(-1);
	return (fd);
}

int	handle_herdoc_iredr(t_parsing_node *node, t_exec_struct *exec_s)
{
	int	in;

	(void)exec_s;
	in = -1;
	if (node->last_in_token == EOL)
		return (0);
	else if (node->last_in_token == REDRI)
	{
		in = handle_input_redirect(node);
	}
	dup2(in, 0);
	close(in);
	return (0);
}
