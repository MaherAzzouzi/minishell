#include "minishell.h"

#ifndef EXEC_H
#define EXEC_H

#include "builtins.h"

void execute(t_parsing_node *root, t_exec_struct *exec_s, t_envp **env);
void free_charpp(char **p);
char *get_env(char *var, void *exec_s, int flag);
char *check_if_bin_exist(char *bin_name, char *path_env);

char **show_envp(char *envp[]);
void init(t_exec_struct *exec_s, char *envp[]);
int show_errno();

int is_input_redirected(t_parsing_node *node);
int is_output_redirected(t_parsing_node *node);
int is_heredoc(t_parsing_node *node);
int is_append(t_parsing_node *node);
int handle_output_redirect(t_parsing_node *node);
int handle_herdoc(t_parsing_node *node, t_exec_struct *exec_s);
int handle_append(t_parsing_node *node);
int handle_append_oredr(t_parsing_node *node);
int handle_herdoc_iredr(t_parsing_node *node, t_exec_struct *exec_s);
int exec_simple_cmd(t_parsing_node *node, t_exec_struct *exec_s, t_envp **env);
void pipe_chain_exec(t_parsing_node *node, t_exec_struct *exec_s, t_envp **env);
void and_chain_exec(t_parsing_node *node, t_exec_struct *exec_s, t_envp *env);
void or_chain_exec(t_parsing_node *node, t_exec_struct *exec_s, t_envp *env);
int it_has_herdoc(t_parsing_node *node);
void convert(t_envp *env);
void enter();
void ctrl_c_handler();

typedef struct s_sp_params
{
	int				in;
	int				out;
	t_parsing_node	*root;
	t_exec_struct	*exec_s;
	int				*fd;
	t_envp			**env;
}	t_spp;

char	*return_cmd_full_path(t_parsing_node *root, t_exec_struct *exec_s);
void	spawn_process_builtins(t_spp *s);
void	spawn_process_sc(t_spp *s, char *p, struct stat *sb);
void	spawn_process_handle_io(t_spp *s);
void	spawn_process_child(t_spp *s);
pid_t	spawn_process(t_spp *s);
void	pipe_chain_exec_hoc(t_parsing_node *node, int *fd,
								t_exec_struct *exec_s, t_envp **env);
void	pipe_chain_exec_rc(t_parsing_node *node, int *fd,
		t_exec_struct *exec_s, t_envp **env);
void	pipe_chain_exec(t_parsing_node *node,
			t_exec_struct *exec_s, t_envp **env);
int	exec_simple_cmd_builtin(t_parsing_node *node, t_exec_struct *exec_s,
				t_envp **env);
void	exec_simple_cmd_core(char *p, struct stat *sb, t_parsing_node *node);
int	exec_simple_cmd_prt(pid_t pid);
void	exec_simple_cmd_child(t_parsing_node *node, t_envp **env);
int	exec_simple_cmd(t_parsing_node *node, t_exec_struct *exec_s, t_envp **env);
char	*get_next_line(int fd);
void	free_charpp(char **p);
void	reverse(char *p);
char	*itoa(int d);
char	*get_env(char *var, void *exec_s, int flag);
char	*check_if_bin_exist(char *bin_name, char *path_env);
int	is_input_redirected(t_parsing_node *node);
int	is_output_redirected(t_parsing_node *node);
int	it_has_herdoc(t_parsing_node *node);
int	it_has_append(t_parsing_node *node);
int	handle_output_redirect(t_parsing_node *node);

#endif