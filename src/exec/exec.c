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

pid_t spawn_process(int in, int out, t_parsing_node *root, t_exec_struct *exec_s)
{
    pid_t pid;

    printf("Executing %s\n", root->cmd.cmd);
    pid = fork();
    if (pid == 0)
    {
        char *p;

        if (in != 0)
        {
            dup2(in, 0);
            close(in);
        }

        if (out != 1)
        {
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
        if (in != 0)
            close(in);
        if (out != 1)
            close(out);
        return (pid);
    }
}

void show_content(int fd)
{
    char p[4096];
    int ret;

    ret = read(fd, p, 4096);
    write(1, p, ret);
}

// void recursive_exec(t_parsing_node *node, t_exec_struct *exec_s, int out)
// {
//     int fd[2];
//     static int f;
//     int pid1;
//     int pid2;
//     int status;

//     pid1 = 0;
//     pid2 = 0;
//     printf("type = %s\n", convert_token(node->type));
//     if (node->type == PIPE)
//     {
//         pipe(fd);
//         printf("Here\n");
//         if (node->lchild->type == CMD && node->rchild->type == CMD)
//         {
//             if (f == 0)
//             {
//                 pid1 = spawn_process(0, fd[1], node->rchild, exec_s);
//                 printf("pid1 %d\n", pid1);
//                 f = 1;
//             }
//             pid2 = spawn_process(fd[0], out, node->lchild, exec_s);
//             printf("pid2 %d\n", pid2);
//             waitpid(pid2, &status, 0);
//             if (f == 0)
//                 waitpid(pid1, &status, 0);
//             printf("END\n");
//             node->type = CMD;
//             return ;
//         }
//     }
//     printf("Here2\n");
//     recursive_exec(node->rchild, exec_s, fd[1]);
//     printf("Here3\n");
//     recursive_exec(node, exec_s, out);
// }

// void recursive_exec(t_parsing_node *node, t_exec_struct *exec_s)
// {
//     static int fd[2];
//     //int status;
//     // int pid1;
//     // int pid2;

//     if (node->type == PIPE)
//     {
//         pipe(fd);
//         spawn_process(0, fd[1], node->lchild, exec_s);
//         wait(NULL);
//         dup2(fd[0], 0);

//         pipe(fd);
//         node = node->rchild;
//         spawn_process(0, fd[1], node->lchild, exec_s);
//         spawn_process(fd[0], 1, node->rchild, exec_s);

//         node = node->rchild;
        

//         wait(NULL);
//     }
//     //show_content(fd[1]);
// }

void save_old_io()
{
    int fd[2];

    fd[0] = dup(0);
    fd[1] = dup(1);
}

void restore_io()
{

}

void recursive_exec(t_parsing_node *node, t_exec_struct *exec_s)
{
    static int fd[2];
    //int status;
    // int pid1;
    // int pid2;
    int fd2;

    fd2 = dup(0);
    while (node->type == PIPE)
    {
        pipe(fd);
        spawn_process(0, fd[1], node->lchild, exec_s);

        if (node->rchild->type == CMD)
        {
            spawn_process(fd[0], 1, node->rchild, exec_s);
        }
        else
        {
            dup2(fd[0], 0);
        }
        wait(NULL);
        node = node->rchild;
    }
    dup2(fd2, 0);
    close(fd2);
}

void execute(t_parsing_node *root, t_exec_struct *exec_s, char *envp[])
{
    init(exec_s, envp);
    builtins(root);

    //spawn_process(0, 1, root, exec_s);
    recursive_exec(root, exec_s);
}