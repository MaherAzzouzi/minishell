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

// Need to use access before opening.
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
    fd = open(node->reds.o_r_params[i], O_CREAT | O_WRONLY | O_TRUNC, 0664);
    printf("redirect to %s\n", node->reds.o_r_params[i]);
    if (fd < 0)
    {
        printf("Error creating file %s\n", node->reds.o_r_params[i]);
        exit(-1);
    }
    return (fd);
}

// Now append >>

int handle_append(t_parsing_node *node)
{
    int i;
    int fd;

    if (!it_has_append(node))
        return (-1);
    // We just set the output to the last file in our list.

    i = 0;
    while (node->reds.append_array[i] && node->reds.append_array[i + 1])
    {        
        fd = open(node->reds.append_array[i], O_CREAT , 0664);
        if (fd < 0)
        {
            printf("Error creating file %s\n", node->reds.append_array[i]);
            exit(-1);
        }
        i++;
    }
    fd = open(node->reds.append_array[i], O_CREAT | O_WRONLY | O_APPEND, 0664);
    printf("redirect to %s\n", node->reds.append_array[i]);
    if (fd < 0)
    {
        printf("Error creating file %s\n", node->reds.append_array[i]);
        exit(-1);
    }
    return (fd);
}


// This function will redirect the output of the child!
int handle_append_oredr(t_parsing_node *node)
{
    int out;

    if (node->last_out_token == EOL)
        return 0;
    else if (node->last_out_token == REDRO)
    {
        out = handle_output_redirect(node);
        handle_append(node);
    }
    else if (node->last_out_token == APPND)
    {
        out = handle_append(node);
        handle_output_redirect(node);
    }
    
    dup2(out, 1);
    close(out);
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
    close(fd[1]);
    return (fd[0]);
}

// Now we come to input like this <
int handle_input_redirect(t_parsing_node *node)
{
    int i;
    int fd;

    if (!is_input_redirected(node))
        return (-1);
    
    i = 0;
    while (node->reds.i_r_params[i] && node->reds.i_r_params[i + 1] != NULL)
    {
        fd = open(node->reds.i_r_params[i], O_CREAT , 0664);
        if (fd < 0)
        {
            printf("Error creating file %s\n", node->reds.i_r_params[i]);
            exit(-1);
        }
        i++;
    }
    // The actual file we want to redirect the output to.
    if (access(node->reds.i_r_params[i], R_OK) != 0)
        show_errno();
    fd = open(node->reds.i_r_params[i], O_RDONLY, 0664);
    printf("redirect to %s\n", node->reds.i_r_params[i]);
    if (fd < 0)
    {
        printf("Error creating file %s\n", node->reds.o_r_params[i]);
        exit(-1);
    }
    return (fd);
}

// This function will redirect the input of the child!
int handle_herdoc_iredr(t_parsing_node *node)
{
    int in;

    if (node->last_in_token == EOL)
        return (0);
    else if (node->last_in_token == REDRI)
    {
        in = handle_input_redirect(node);
        handle_herdoc(node);
    }
    else if (node->last_in_token == DLMI)
    {
        in = handle_herdoc(node);
        handle_input_redirect(node);
    }
    
    // Make it read from here!
    dup2(in, 0);
    close(in);
    return (0);
}