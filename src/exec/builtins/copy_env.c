#include "minishell.h"

t_envp	*node_env(char *str)
{
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	node->str = ft_strdup(str);
	node->next = NULL;
	return (node);
}

t_envp	*new_env(t_envp **head, char *str)
{
	t_envp	*new_node;
	t_envp	*curr;

	new_node = node_env(str);
	curr = *head;
	if (! *head)
	{
		*head = new_node;
		return (*head);
	}
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
	new_node->next = NULL;
	return (*head);
}

t_envp	*ennv(t_exec_struct *exec)
{
	t_envp	*test;
	int		i;

	test = NULL;
	i = 0;
	while (exec->envp[i])
	{
		new_env(&test, exec->envp[i]);
		i++;
	}
	return (test);
}

t_envp	*exxport(t_envp **envp)
{
	t_envp	*dup_env;
	t_envp	*curr;

	dup_env = NULL;
	curr = *envp;
	while (curr)
	{
		new_env(&dup_env, curr->str);
		curr = curr->next;
	}
	return (dup_env);
}
