/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:14:50 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:14:51 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parsing_node	*parse(t_lnode **head, t_exec_struct *exec_s)
{
	t_parsing_node	*root;

	consolidate_dlr_with_cmd(head, exec_s);
	flag_env_variables(*head);
	if ((order_quotes(head) == FAIL || check_all(*head) == FAIL))
	{
		exit_status_fail();
		printf("Syntax Error!\n");
		return (NULL);
	}
	replace_dlr_with_flag(*head);
	join_quotes(*head);
	clean_empty_quote(head, SGLQT);
	clean_empty_quote(head, DBLQT);
	consolidate_commands(head);
	handle_wildcard(*head);
	root = parse_tree(*head);
	return (root);
}
