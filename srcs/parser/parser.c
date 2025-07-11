/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:58:24 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/26 21:47:21 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "tokenizer.h"

t_ast_type	ft_ast_fromtoken(t_token_type type);

t_ast	*ft_ast_simplecommand(t_token **token)
{
	t_token_type	token_type;
	t_ast			*node;

	if (*token == NULL)
		return (NULL);
	node = ft_ast_new(AST_SIMPLE_COMMAND);
	while (1)
	{
		token_type = (*token)->type;
		if (token_type == TOKEN_WORD)
			ft_list_token_push(&node->args, *token);
		else if (ft_token_isredirect(token_type))
		{
			if (!ft_ast_redirect(token, node))
				return (NULL);
		}
		else
			break ;
		*token = (*token)->next;
	}
	if (node->redirect == NULL && node->args == NULL)
		return (NULL);
	return (node);
}

t_ast	*ft_ast_subshell(t_token **token)
{
	t_ast	*child_node;

	if (!*token || (*token)->type != TOKEN_PARENS_OPEN)
		return (NULL);
	*token = (*token)->next;
	child_node = ft_ast_andor(token);
	if (!child_node || (*token)->type != TOKEN_PARENS_CLOSE)
		return (NULL);
	*token = (*token)->next;
	child_node->type = AST_SUBSHELL;
	return (child_node);
}

t_ast	*ft_ast_command(t_token **token)
{
	t_ast	*node;

	if (*token == NULL)
		return (NULL);
	node = ft_ast_simplecommand(token);
	if (node)
		return (node);
	node = ft_ast_subshell(token);
	if (!node)
		return (NULL);
	while (*token && ft_token_isredirect((*token)->type))
	{
		if (!ft_ast_redirect(token, node))
			return (NULL);
		*token = (*token)->next;
	}
	return (node);
}

t_ast	*ft_ast_pipeline(t_token **token)
{
	t_token_type	token_type;
	t_ast			*node_parent;
	t_ast			*node_child;

	node_child = ft_ast_command(token);
	if (node_child == NULL || (*token)->type != TOKEN_PIPE)
		return (node_child);
	node_parent = ft_ast_new(AST_PIPELINE);
	ft_ast_push(node_parent, node_child);
	while (1)
	{
		token_type = (*token)->type;
		if (token_type == TOKEN_PIPE)
		{
			*token = (*token)->next;
			node_child = ft_ast_command(token);
			if (node_child == NULL)
				return (NULL);
			ft_ast_push(node_parent, node_child);
		}
		else
			break ;
	}
	return (node_parent);
}

t_ast	*ft_ast_andor(t_token **token)
{
	t_token_type	token_type;
	t_ast			*node_child;
	t_ast			*node_parent;

	node_child = ft_ast_pipeline(token);
	if (node_child == NULL)
		return (NULL);
	node_parent = ft_ast_new(AST_AND_OR);
	ft_ast_push(node_parent, node_child);
	while (1)
	{
		token_type = (*token)->type;
		if (token_type == TOKEN_OR || token_type == TOKEN_AND)
		{
			ft_ast_push(node_parent, ft_ast_new(ft_ast_fromtoken(token_type)));
			*token = (*token)->next;
			node_child = ft_ast_pipeline(token);
			if (node_child == NULL)
				return (NULL);
			ft_ast_push(node_parent, node_child);
		}
		else
			break ;
	}
	return (node_parent);
}
