/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:10:12 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/25 11:00:32 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parser.h"
#include "tokenizer.h"

t_ast	*ft_ast_new(t_ast_type ast_type)
{
	t_ast	*node;

	node = ft_malloc(sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->args = NULL;
	node->children = NULL;
	node->redirect = NULL;
	node->type = ast_type;
	return (node);
}

t_list	*ft_ast_push(t_ast *parent, t_ast *child)
{
	t_list	*lst;

	if (parent == NULL)
		return (NULL);
	lst = ft_lstnew(child);
	ft_collector_track(lst);
	if (lst == NULL)
		return (NULL);
	ft_lstadd_back(&parent->children, lst);
	return (lst);
}

t_list	*ft_list_token_push(t_list **head, t_token *token)
{
	t_list	*lst;

	if (head == NULL)
		return (NULL);
	lst = ft_lstnew(token);
	if (lst == NULL)
		return (NULL);
	ft_collector_track(lst);
	ft_lstadd_back(head, lst);
	return (lst);
}

void	ft_ast_nextchild_withtype(t_list **p, t_ast_type type)
{
	t_ast	*child;

	if (p == NULL || *p == NULL)
		return ;
	while ((*p)->next)
	{
		child = (*p)->content;
		if (child->type == type)
			break ;
		*p = (*p)->next;
	}
}
