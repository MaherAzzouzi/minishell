#ifndef CHECKS_H
# define CHECKS_H

int two_successive_pars(t_lnode *head);
int check_all(t_lnode *head);
int check_condt_syntax_errors(t_lnode* head);
int check_left_right(t_lnode* condt, t_lnode *head);
t_lnode *return_condt_addr(t_lnode    *head);


# endif