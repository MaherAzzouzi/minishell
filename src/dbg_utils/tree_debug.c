#include "parser.h"


void show_reds_node(char *name, char **p, char *cmd_name)
{
	int i;
	
	if (cmd_name)
		printf("%s ", cmd_name);
	if (p)
	{
		if (name)
			printf("%s ", name);
		i = 0;
		printf("\t[");
		while (p[i])
		{
			printf("%s ", p[i]);
			i++;
		}
		printf("]\n");
	}
}

void show_node(t_parsing_node *node)
{
	printf("------------------------------\n");
	if (node->type == CMD)
	{
		show_reds_node(NULL, node->cmd.argv, node->cmd.cmd);
		show_reds_node("'>' ", node->reds.i_r_params, NULL);
		show_reds_node("'<' ", node->reds.o_r_params, NULL);
		show_reds_node("'>>'", node->reds.append_array, NULL);
		show_reds_node("'<<'", node->reds.herdoc_array, NULL);
		
		if (node->p.parenthesised)
		{
			printf("() -> %s\n", node->p.cmd);
		}
	}
	else
		printf("%s\n", enum_to_str(node->type));
}

void inorder_show(t_parsing_node *root)
{
	if (root == NULL)
		return;
	inorder_show(root->lchild);
	show_node(root);
	inorder_show(root->rchild);
}
