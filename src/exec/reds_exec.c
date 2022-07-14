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

int handle_output_redirect(t_parsing_node *node)
{
    int i;
    int fd;

    if (!is_output_redirected(node))
        return (-1);
    
    printf("REDOUTPUT!\n");
    while (node->reds.o_r_params[i] && node->reds.o_r_params[i + 1] != NULL)
    {
        fd = open(node->reds.o_r_params[i], O_CREAT);
        if (fd < 0)
        {
            printf("Error creating file %s\n", node->reds.o_r_params[i]);
            exit(-1);
        }
        i++;
    }
    // The actual file we want to redirect the output to.
    fd = open(node->reds.o_r_params[i], O_CREAT | O_WRONLY);
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