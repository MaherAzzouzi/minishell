#include "minishell.h"

char *return_cmd_full_path(t_parsing_node *root, t_exec_struct *exec_s)
{
    char *p;

    if (root->cmd.cmd[0] != '/')
        p = check_if_bin_exist(root->cmd.cmd, exec_s->path);
    else
        p = root->cmd.cmd;
    return p;
}

void spawn_process(int in, int out, t_parsing_node *root, t_exec_struct *exec_s)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        char *p;

        if (in != 0)
        {
            printf("Changing stdin\n");
            dup2(in, 0);
            close(in);
        }

        if (out != 1)
        {
            printf("Changing stdout\n");
            dup2(out, 1);
            close(out);
        }

        p = return_cmd_full_path(root ,exec_s);
        if (p == NULL)
            show_errno();
        execve(p, root->cmd.argv, exec_s->envp);
        exit(0);
    }
    else
    {
        int status;
        if (in != 0)
            close(in);

        if (out != 1)
            close(out);
        waitpid(pid, &status, 0);
    }
}

void recursive_exec(t_parsing_node *node, t_exec_struct *exec_s, int out)
{
    int fd[2];

    if (node->type == PIPE)
    {
        pipe(fd);
        if (node->lchild->type == CMD && node->rchild->type == CMD)
        {
            if (out != 1)
                spawn_process(0, fd[1], node->lchild, exec_s);
            spawn_process(fd[0], out, node->rchild, exec_s);
            node->type = CMD;
            return ;
        }
    }
    recursive_exec(node->lchild, exec_s, fd[1]);
    recursive_exec(node, exec_s, out);
}

void execute(t_parsing_node *root, t_exec_struct *exec_s, char *envp[])
{
    init(exec_s, envp);
    builtins(root);

    //spawn_process(0, 1, root, exec_s);
    recursive_exec(root, exec_s, 1);
}