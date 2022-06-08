#include "minishell.h"

void free_node(t_parsing_node *node)
{
	int i;

	if (node->cmd.cmd)
		free(node->cmd.cmd);
	if (node->cmd.argv)
	{
		i = 0;
		while (node->cmd.argv[i])
		{
			free(node->cmd.argv[i]);
			i++;
		}
		free(node->cmd.argv);
	}
	free(node);
}

void free_tree(t_parsing_node *root)
{
	if (root == NULL)
		return;
	free_tree(root->lchild);
	free_tree(root->rchild);
	free_node(root);
}