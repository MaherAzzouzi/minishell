#include "parser.h"


void show_reds_node(char *name, char **p, char *cmd_name)
{
	int i;
	
	if (cmd_name)
		fprintf(stderr,"%s ", cmd_name);
	if (p)
	{
		if (name)
			fprintf(stderr,"%s ", name);
		i = 0;
		fprintf(stderr,"\t[");
		while (p[i])
		{
			fprintf(stderr,"%s ", p[i]);
			i++;
		}
		fprintf(stderr,"]\n");
	}
}

void show_herdoc_node(char *name, struct herdoc_exp **p, char *cmd_name)
{
	int i;
	
	if (cmd_name)
		fprintf(stderr,"%s ", cmd_name);
	if (p)
	{
		if (name)
			fprintf(stderr,"%s ", name);
		i = 0;
		fprintf(stderr,"\t[");
		while (p[i])
		{
			fprintf(stderr,"%s %d", p[i]->herdoc_keyword, p[i]->is_quoted);
			i++;
		}
		fprintf(stderr,"]\n");
	}
}

void show_node(t_parsing_node *node)
{
	printf("------------------------------\n");
	if (node->type == CMD)
	{
		show_reds_node(NULL, node->cmd.argv, node->cmd.cmd);
		show_reds_node("'>' ", node->reds.o_r_params, NULL);
		show_reds_node("'<' ", node->reds.i_r_params, NULL);
		show_reds_node("'>>'", node->reds.append_array, NULL);
		show_herdoc_node("'<<'", node->reds.herdoc_array, NULL);
		
		if (node->p.parenthesised)
		{
			fprintf(stderr ,"() -> %s\n", node->p.cmd);
		}
	}
	else
		fprintf(stderr, "%s\n", enum_to_str(node->type));
}

void inorder_show(t_parsing_node *root)
{
	if (root == NULL)
		return;
	inorder_show(root->lchild);
	show_node(root);
	inorder_show(root->rchild);
}

void preorder_show(t_parsing_node *root)
{
	if (root == NULL)
		return;
	show_node(root);
	inorder_show(root->lchild);
	inorder_show(root->rchild);
}