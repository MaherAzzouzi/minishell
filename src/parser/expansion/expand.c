#include "minishell.h"

// For Linux the env variables can have an uppercase/lowercase or number + underscore
// May require some fixes for macOS

// An idea that I got to fix that ' quote expansion is to add a \xff at the end
// Marking that it should not expand.


// This function should get a pointer to the dollar sign and then something like this $HOME
int get_env_variable_length(char *p)
{
    char *q;
    char *t;

    if (p[0] != '$')
        return FAIL;
    // bypass $
    p++;
    
    if (p[0] == '\xfe')
    {
        return 1;
    }

    if (*p == '$' || *p == '?')
        return 1;
    if (ft_isdigit(*p))
        return 1;
    q = p;
    while (*p != 0)
    {
        t = p;
        while (ft_isalnum(*p))
            p++;
        while (*p == '_')
            p++;
        if (*p == '\xfe')
        {
            p++;
            break;
        }
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

char * remove_char(char *p, char c)
{
    int i;
    int j;

    i = 0;
    while (p[i])
    {
        if (p[i] == c)
        {
            j = i + 1;
            while (p[i] != 0)
            {
                p[i] = p[j];
                i++;
                j++;
            }
            p[i] = 0;
            i = -1;
        }
        i++;
    }
    return p;
}

char *expand_an_array_having_dlr(char *p, t_exec_struct* exec_s)
{
    char* result;
    char* q;
    char    *env;
    //int flag;

    //flag = 0;
    result = NULL;

    while (1)
    {
        q = strchr(p, '$');
        if (q == NULL)
        {
            break;
        }
        if (q[1] == 0)
        {
            break;
        }
        env = return_env(q);
        result = (char *)malloc((q - p + 1)*sizeof(char));
        if (result == NULL)
            exit(-1);
        ft_memcpy(result, p, q-p);
        result[q-p] = 0;
        if (env[0] == '\xfe' && env[1] == 0)
        {
            result = ft_strjoin(result, get_env(env, exec_s, 0), 2);
            result = ft_strjoin(result, q+ft_strlen(env)+1, 0);
        }
        else if (strchr(env, '\xfe'))
        {
            env[ft_strlen(env) - 1] = 0;
            result = ft_strjoin(result, get_env(env, exec_s, 0), 2);
            result = ft_strjoin(result, q+ft_strlen(env)+2, 0);
        }
        else
        {
            result = ft_strjoin(result, get_env(env, exec_s, 0), 2);
            result = ft_strjoin(result, q+ft_strlen(env)+1, 0);
        }
        free(env);
        free(p);
        p = result;
    }
    if (result)
    {
        replace(result, '\xff', '$');
        remove_char(result, '\xfe');
        return result;
    }
    else
    {
        replace(p, '\xff', '$');
        remove_char(p, '\xfe');
        return p;
    }
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
    // The case when dollar sign is given alone like this "$"
    while (1)
    {
        q = strchr(p, '$');
        if (q == NULL)
        {
            free(node->type.cmd);
            break;
        }
        if (q[1] == 0)
        {
            //p = ft_strjoin(p, "$", 0);
            free(node->type.cmd);
            break;
        }
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

t_lnode * case_of_one_char_dollar(t_lnode **head, t_lnode *current, t_exec_struct* exec_s, int se)
{
    t_lnode *node;
    t_lnode *p;
    char *val;
    (void)exec_s;
    if (se == 0)
    {
        val = ft_strdup("$$");
    }
    else
        val = get_env(convert_token(get_token(current->next)), exec_s, 0);
    node = ft_new_node_lex(CMD, val);
    free(node->type.cmd);
    node->type.cmd = val;
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

char * case_of_one_char_dlr(char *p, t_exec_struct* exec_s)
{
    if (ft_strcmp(p, "$?") == 0 || ft_strcmp(p, "$$") == 0)
    {
        p = get_env(p + 1, exec_s, 0);
        return p;
    }
    else if (ft_strcmp(p, "\xff?") == 0 || ft_strcmp(p, "\xff\xff") == 0)
    {
        replace(p, '\xff', '$');
        return ft_strdup(p);
    }
    return NULL;
}

void expand_one_node(t_parsing_node *node, t_exec_struct* exec_s)
{
    char *p;
    int i;
    if (node->cmd.cmd == NULL || node->cmd.cmd[0] == 0)
        return ;
    
    p = case_of_one_char_dlr(node->cmd.cmd, exec_s);
    if (p == NULL)
    {
        p = expand_an_array_having_dlr(node->cmd.cmd, exec_s);
        if (p != NULL)
        {
            node->cmd.cmd = p;
        }
    }
    else
    {
        free(node->cmd.cmd);
        node->cmd.cmd = p;
    }
    i = 0;
    while (node->cmd.argv[i])
    {
        p = case_of_one_char_dlr(node->cmd.argv[i], exec_s);
        if (p == NULL)
        {
            p = expand_an_array_having_dlr(node->cmd.argv[i], exec_s);
            if (p != NULL)
            {

                node->cmd.argv[i] = p;
            }
        }
        else
        {
            free(node->cmd.argv[i]);
            node->cmd.argv[i] = p;
        }
        i++;
    }
}

void consolidate_dlr_with_cmd(t_lnode **head, t_exec_struct* exec_s)
{
    t_lnode *current;
    t_lnode *p;
    int is_current_changed;

    current = *head;
    while (current && get_token(current) != EOL)
    {
        is_current_changed = 0;
        if (get_token(current) == DLR)
        {
            // If it is $$ or $?
            // Should be handeled here.
            if (get_token(current->next) == DLR)
            {
                current = case_of_one_char_dollar(head, current, exec_s, 0);
                is_current_changed = 1;
            }
            // In this case we just append a dollar at the start
            else if (get_token(current->next) == CMD)
            {
                current->next->type.cmd = ft_strjoin("$", current->next->type.cmd, 1);
                if (current == (*head))
                {
                    p = *head;
                    *head = (*head)->next;
                    current = current->next;
                    free_lexer_node(p);
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
                is_current_changed = 1;
            }
            else
            {
                    current->type.token = CMD;
                    current->type.cmd = ft_strdup("$");
            }
        }
        if (!is_current_changed)
            current = current->next;
    }
    combine_successive_cmds(*head);
}

void expand_env_variables(t_lnode **head, t_exec_struct* exec_s)
{
    //char* value;
    t_lnode *current;
    t_lnode *p;
    int should_expand;

    should_expand = 1;
    current = *head;
    while (current && get_token(current) != EOL)
    {
        if (get_token(current) == DLMI)
        {
            should_expand = 0;
            current = current->next;
        }
        // The case like this echo "$HOME"
        else if (get_token(current) == DBLQT)
        {
            if (should_expand)
            {
                current->next->type.cmd = find_env_expand(current->next, exec_s);
                current = current->next;
            }
            else
            {
                should_expand = 1;
                current = current->next;
            }
        }
        // Now the case if no single of double quotes is given before the dlr sign
        // We should parse it too.
        else if (get_token(current) == DLR)
        {
            // If it is $$ or $?
            // Should be handeled here.
            if (get_token(current->next) == DLR)
            {
                // The case of cat << $$ is not yet handled
                current = case_of_one_char_dollar(head, current, exec_s, should_expand);
                should_expand = 1;
            }
            // In this case we just append a dollar at the start
            else if (get_token(current->next) == CMD)
            {
                current->next->type.cmd = ft_strjoin("$", current->next->type.cmd, 1);
                if (should_expand)
                    current->next->type.cmd = find_env_expand(current->next, exec_s);  
                should_expand = 1;
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
            else //if (get_token(current->next) == EOL)
            {
                    current->type.token = CMD;
                    current->type.cmd = ft_strdup("$");
            }
        }
        else
        {
            current = current->next;
        }
    }
    combine_successive_cmds(*head);
}
