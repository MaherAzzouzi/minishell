/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:24:12 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 20:24:13 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_fail(void)
{
	g_exec_struct->exit_status ^= g_exec_struct->exit_status & 0x0000ff00;
	g_exec_struct->exit_status |= 0x00000100;
}

void	exit_status_success(void)
{
	g_exec_struct->exit_status ^= g_exec_struct->exit_status & 0x0000ff00;
}
