#include "minishell.h"

void update_env(t_envp **en, char *str, char *path)
{
	t_envp	*current;
	char *fr;

	current = *en;
	while(current)
	{
		if (!ft_strncmp(current->str, str, ft_strlen(str)))
		{
			free(current->str);
			fr = ft_strjoin(ft_strdup(str), ft_strdup("="), 2);
			current->str = ft_strjoin(fr, path, 2);
			printf("%s\n", current->str);
		}
		current = current->next;
	}
}