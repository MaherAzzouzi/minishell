#include "minishell.h"

// For Linxu the env variables can have an uppercase/lowercase or number + underscore
// May require some fixes for macOS

// This function should get a pointer to the dollar sign and then something like this $HOME
int get_env_variable_length(char *p)
{
    char *q;
    char *t;

    if (p[0] != '$')
        return FAIL;
    // bypass $
    p++;

    if (*p == '$' || *p == '?')
        return 1;
    q = p;
    while (*p != 0)
    {
        t = p;
        while (ft_isalnum(*p))
            p++;
        while (*p == '_')
            p++;
        if (t == p)
            break;
    }
    // The length of the env variable.
    return (p - q);
}

// should be given something like $HOME
char*   return_env(char *p)
{
    char *env;
    int len;

    len = get_env_variable_length(p);
    env = (char *)malloc((len + 1) * sizeof(char));
    if (env == NULL)
        exit(-1);
    ft_memcpy(env, p+1, len);
    env[len] = 0;
    return env;
}

char* find_env_expand(t_lnode *node, t_exec_struct* exec_s)
{
    char* result;
    char* q;
    char *p;
    char    *env;

    if (get_token(node) != CMD)
        return NULL;

    result = NULL;
    p = ft_strdup(node->type.cmd);
    while (1)
    {
        q = strchr(p, '$');
        if (q == NULL)
            break;
        env = return_env(q);
        result = (char *)malloc((q - p + 1)*sizeof(char));
        if (result == NULL)
            exit(-1);
        ft_memcpy(result, p, q-p);
        result[q-p] = 0;

        result = ft_strjoin(result, get_env(env, exec_s, 0), 2);
        result = ft_strjoin(result, q+ft_strlen(env)+1, 0);
        free(env);
        free(p);
        p = result;
    }

    return p;
}

t_lnode * case_of_one_char_dollar(t_lnode **head, t_lnode *current, t_exec_struct* exec_s)
{
    t_lnode *node;
    t_lnode *p;
    char *val;

    val = get_env(convert_token(get_token(current->next)), exec_s, 0);
    node = ft_new_node_lex(CMD, val);

    if (*head == current)
    {
        *head = node;
    }
    else
    {
        p = *head;
        while (p->next != current)
            p = p->next;

        p->next = node;
    }
    node->next = current->next->next;
    free_lexer_node(current->next);
    free_lexer_node(current);
    return node->next;
}

void combine_successive_cmds(t_lnode *head)
{
    t_lnode *current;
    t_lnode *tmp;
    int flag;

    flag = 1;
    while (flag)
    {
        flag = 0;
        current = head;
        while (get_token(current) != EOL)
        {
            if (get_token(current) == CMD && get_token(current->next) == CMD)
            {
                current->type.cmd = ft_strjoin(current->type.cmd, current->next->type.cmd, 0);
                tmp = current->next->next;
                free_lexer_node(current->next);
                current->next = tmp;
                flag = 1;
            }
            current = current->next;
        }
    }
}

void expand_env_variables(t_lnode **head, t_exec_struct* exec_s)
{
    //char* value;
    t_lnode *current;
    t_lnode *p;

    current = *head;
    while (current && get_token(current) != EOL)
    {
        // The case like this echo "$HOME"
        if (get_token(current) == DBLQT)
        {
            //free(current->next->type.cmd);
            current->next->type.cmd = find_env_expand(current->next, exec_s);
            current = current->next;
        }
        // Now the case if no single of double quotes is given before the dlr sign
        // We should parse it too.
        else if (get_token(current) == DLR)
        {
            // If it is $$ or $?
            // Should be handeled here.
            if (get_token(current->next) == DLR)
            {
                current = case_of_one_char_dollar(head, current, exec_s);
            }
            // In this case we just append a dollar at the start
            else if (get_token(current->next) == CMD)
            {
                current->next->type.cmd = ft_strjoin("$", current->next->type.cmd, 1);
                current->next->type.cmd = find_env_expand(current->next, exec_s);
                
                if (current == (*head))
                {
                    *head = (*head)->next;
                    current = current->next;
                }
                else
                {
                    p = *head;
                    while (p->next != current)
                        p = p->next;
                    p->next = current->next;
                    free_lexer_node(current);
                    current = p->next;
                }
            }
            // simple dolar sign should work too.
            // else
            // {

            // }
        }
        else
            current = current->next;
    }
    combine_successive_cmds(*head);
}