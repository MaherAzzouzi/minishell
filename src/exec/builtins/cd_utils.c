#include "minishell.h"

void update_env(t_envp **en, char *str, char *path)
{
	t_envp *current;
	char *fr;

	fr = NULL;
	current = *en;
	while (current)
	{
		//printf("CMP %s,%s\n", current->str, str);
		if (!ft_strncmp(current->str, str, ft_strlen(str)))
		{
			free(current->str);
			//getchar();
			fr = ft_strjoin(str, "=", 3);
			current->str = ft_strjoin(fr, path, 0);
		}
		current = current->next;
	}
	free(str);
}