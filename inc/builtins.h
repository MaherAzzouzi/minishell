/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mriskyin <Mriskyin-team@student.42.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 22:20:19 by Mriskyin          #+#    #+#             */
/*   Updated: 2022/08/31 22:21:40 by Mriskyin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_envp{
	char			*str;
	struct s_envp	*next;
}	t_envp;

int		builtins(t_parsing_node *root, t_exec_struct *exec_s, t_envp **env);
void	ft_echo(t_parsing_node *root);
int		ft_cd(t_parsing_node *root, t_envp *env);
int		ft_pwd(t_parsing_node *node, t_envp *env);
int		ft_env(t_parsing_node *node, t_envp **env);
t_envp	*ennv(t_exec_struct *exec);
void	update_env(t_envp **en, char *str, char *path);
char	*find_env(char *str, t_envp *env);
void	ft_exit(t_parsing_node *root, t_exec_struct *exec_s);
void	ft_unset(t_parsing_node *root, t_envp **env);
t_envp	*exxport(t_envp **envp);
int		ft_export(t_parsing_node *node, t_envp **env);
int		check_export_syntax(char *str);
t_envp	*new_env(t_envp **head, char *str);
int		ft_egale_len(char *str);
int		check_new_env(char *str, t_envp	**env);
int		ft_check_var_syntx(char *str);
void	free_env(t_envp **head);
int		is_builtin(t_parsing_node *root);
char	*ft_strndup(char *str, int j);
int		check_equal(char *str);
char	*find_env(char *str, t_envp *env);
int		change_dir_old(char *str, t_envp *env);
char	*get_cwd(void);
void	updating_envs(char *curr_path, t_envp *en, char *new_path);
int		change_dir(char *dir, t_envp *en);
void	free_env(t_envp **head);
int		ft_isalnum2(int c);
char	*ft_strndup(char *str, int j);
int		ft_check_var_syntx(char *str);
void	set_ar_w_e_o_n(char **s, char *str);
int		ft_egale_len(char *str);
void	ft_sort_export(t_envp *head);
void	print_exp(int len, char *str, int *i);
void	p_(char *str, int len);
int		checking_new_env(t_parsing_node *node, t_envp **env, t_envp *export);

#endif