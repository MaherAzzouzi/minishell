#ifndef UTILS_H
# define UTILS_H

int is_empty(char *p);
int is_even(int num);
int is_odd(int num);
void ignore_spaces(t_lnode **head);
void free_tree(t_parsing_node *root);
int count_token(t_lnode* head, t_lnode *current, e_token t);

# endif