#include "parser.h"

void show_node(t_parsing_node *node)
{
	if (node->type == CMD)
	{
		int i;
		//printf("ok\n");
		printf("%s [", node->cmd.cmd);
		i = 0;
		while (node->cmd.argv && node->cmd.argv[i])
			printf("%s, ", node->cmd.argv[i++]);
		printf("]\n");
		if (node->reds.i_r_params)
		{	
			printf("--> '<' <--");
			i = 0;
			printf("\n[\n");
			while (node->reds.i_r_params[i])
			{
				printf("---->%s\n", node->reds.i_r_params[i]);
				i++;
			}
			printf("]\n");
		}
		i = 0;
		if (node->reds.o_r_params)
		{	
			printf("--> '>' <--");
			i = 0;
			printf("\n[\n");
			while (node->reds.o_r_params[i])
			{
				printf("---->%s\n", node->reds.o_r_params[i]);
				i++;
			}
			printf("]\n");
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
