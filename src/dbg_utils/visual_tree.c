/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visua_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:16:26 by snagat            #+#    #+#             */
/*   Updated: 2022/06/15 11:21:25 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#define COUNT 10
#include <minishell.h>







void print2DUtil(t_parsing_node *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->rchild, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%s\n", enum_to_str(root->type));
 
    // Process left child
    print2DUtil(root->lchild, space);
}


void print2D(t_parsing_node *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}