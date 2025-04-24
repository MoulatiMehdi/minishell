/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:10:12 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/23 15:50:12 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collector.h"
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

void	*ft_token_dup(t_token *token)
{
	t_token	*token_cp;

	if (token == NULL)
		return (NULL);
	token_cp = ft_malloc(sizeof(t_token));
	if (token_cp == NULL)
		return (NULL);
	token_cp->next = NULL;
	token_cp->length = token->length;
	token_cp->type = token->type;
	token_cp->value = token->value;
	return (token_cp);
}

void	ft_lstnode_clear(t_list *head)
{
	t_list	*curr;

	while (head)
	{
		curr = head->next;
		ft_free(head);
		head = curr;
	}
}

t_ast	*ft_ast_free(t_ast *head)
{
	ft_lstnode_clear(head->args);
	ft_lstnode_clear(head->children);
	ft_lstnode_clear(head->redirect);
	ft_free(head);
    return NULL;
}
