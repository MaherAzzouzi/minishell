#include "minishell.h"

char **show_envp(char *envp[])
{
    int i;

    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
    return NULL;
}

void execute(t_parsing_node *root, char *envp[])
{
    //pid_t pid;

    (void)root;

    show_envp(envp);
    builtins(root);
    /*
    pid = fork();
    if (pid == 0)
    {
        printf("Executing %s\n", root->cmd.cmd);
        printf("ARGV %s\n", root->cmd.argv[0]);
        execve(root->cmd.cmd, root->cmd.argv, envp);
        exit(0);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
    */
}