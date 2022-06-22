#include "minishell.h"

void execute(t_parsing_node *root, t_exec_struct *exec_s, char *envp[])
{
    pid_t pid;
    (void)root;

    if (exec_s->path == NULL)
        exec_s->path = get_env("PATH", envp);
    
    pid = fork();
    if (pid == 0)
    {
        char *p;

        p = check_if_bin_exist(root->cmd.cmd, exec_s->path);
        if (p == NULL)
            show_errno();
        printf("Executing %s\n", p);
        execve(p, root->cmd.argv, envp);
        exit(0);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
    
}