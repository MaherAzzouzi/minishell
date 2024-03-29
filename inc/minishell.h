/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 22:53:14 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 23:31:26 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <sys/stat.h>
# include "lexer.h"
# include "parser.h"
# include "utils.h"
# include "libft.h"
# include "ft_printf.h"
# include "redirections.h"
# include "checks.h"
# include "exec.h"
# include "builtins.h"
# include <sys/types.h>
# include <dirent.h>
# include <termios.h>
# include <unistd.h>
# include <sys/ioctl.h>

t_exec_struct	*g_exec_struct;

# define TRUE 1
# define FALSE 0
# define INFINIT 666
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define WHITE "\033[0;37m"
# define SUCCESS 0
# define FAIL -1
# define FOUND 1
# define NOT_FOUND 0

void	free_list(t_lnode **head);
int		order_quotes(t_lnode **head);
void	fix_after_expansion(t_lnode *head);
void	exit_status_success(void);
void	exit_status_fail(void);
void	show_errno_no_exit(char *file);
void	show_message(char *file, char *msg);
int		core(char *cmd, char *envp[], t_exec_struct *exec_struct, t_envp **env);
void	loop_handler(char *envp[], t_exec_struct *exec_s);
char	*read_command_line(t_exec_struct *exec_struct);
void	ctrl_c_handler(int p);
void	enter(int p);
#endif
