#include "minishell.h"

int show_errno(char *file)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(file, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
    exit(-1);
}

void show_errno_no_exit(char *file)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(file, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
}

void show_message(char *file, char *msg)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(file, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
}