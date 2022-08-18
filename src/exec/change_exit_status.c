#include "minishell.h"

void exit_status_fail(void)
{
	g_exec_struct->exit_status ^= g_exec_struct->exit_status & 0x0000ff00;
    g_exec_struct->exit_status |= 0x00000100;
}

void exit_status_success(void)
{
    g_exec_struct->exit_status ^= g_exec_struct->exit_status & 0x0000ff00;
}

