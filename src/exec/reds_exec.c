#include "minishell.h"

int is_input_redirected(t_parsing_node *node)
{
    if (node->reds.i_r_params && node->reds.i_r_params[0])
        return (1);
    return (0);
}

int is_output_redirected(t_parsing_node *node)
{
    if (node->reds.o_r_params && node->reds.o_r_params[0])
        return (1);
    return (0);
}

int it_has_herdoc(t_parsing_node *node)
{
    if (node->reds.herdoc_array && node->reds.herdoc_array[0])
        return (1);
    return (0);
}

int it_has_append(t_parsing_node *node)
{
    if (node->reds.append_array && node->reds.append_array[0])
        return (1);
    return (0);
}

// cat t >t>f>y (t should become empty)
int handle_output_redirect(t_parsing_node *node)
{
    int i;
    int fd;

    if (!is_output_redirected(node))
        return (-1);
    
    printf("REDOUTPUT!\n");

    i = 0;
    while (node->reds.o_r_params[i] && node->reds.o_r_params[i + 1] != NULL)
    {
        fd = open(node->reds.o_r_params[i], O_CREAT , 0664);
        if (fd < 0)
        {
            printf("Error creating file %s\n", node->reds.o_r_params[i]);
            exit(-1);
        }
        i++;
    }
    // The actual file we want to redirect the output to.
    fd = open(node->reds.o_r_params[i], O_CREAT | O_WRONLY, 0664);
    printf("redirect to %s\n", node->reds.o_r_params[i]);
    if (fd < 0)
    {
        printf("Error creating file %s\n", node->reds.o_r_params[i]);
        exit(-1);
    }

    // We need to make it the stdout for the process.
    dup2(fd, 1);
    close(fd);

    return (0);
}

// <<

int handle_herdoc(t_parsing_node *node)
{
    int i;
    int fd[2];
    char *p;

    if (!it_has_herdoc(node))
        return (-1);
    // Open a pipe
    // Keep reading until the last herdoc which is interesting
    // Open a pipe to use it as input for our program

    i = 0;
    while (node->reds.herdoc_array[i] && node->reds.herdoc_array[i + 1])
    {
        p = readline("> ");
        if (ft_strcmp(p, node->reds.herdoc_array[i]) == 0)
            i++;
        free(p);
    }

    pipe(fd);
    while (1)
    {
        p = readline("> ");
        if (ft_strcmp(p, node->reds.herdoc_array[i]) == 0)
            break;
        write(fd[1], p, ft_strlen(p));
        write(fd[1], "\n", 1);
        free(p);
    }
    
    // Make it read from here!
    dup2(fd[0], 0);
    close(fd[0]);
    close(fd[1]);
    return 0;
}