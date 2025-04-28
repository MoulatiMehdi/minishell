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

#include "libft/libft.h"
#include "parser.h"
#include "tokenizer.h"

t_ast_type	ft_ast_fromtoken(t_token_type type)
{
	if (type == TOKEN_OR)
		return (AST_OR);
	if (type == TOKEN_AND)
		return (AST_AND);
	if (type == TOKEN_PIPE)
		return (AST_PIPE);
	return (AST_UNKNOWN);
}

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
			ft_lstadd_back(&node->args, ft_lstnew(*token));
		else if (ft_token_isredirect(token_type))
		{
			if ((*token)->value == NULL)
			{
				*token = (*token)->next;
				return (ft_ast_free(node));
			}
			ft_lstadd_back(&node->redirect, ft_lstnew(*token));
		}
		else
			break ;
		*token = (*token)->next;
	}
	if (node->redirect == NULL && node->args == NULL)
		return (ft_ast_free(node));
	return (node);
}

void ft_ast_subshell_optimize(t_ast ** node)
{
    t_ast * node_child;
    t_ast * node_child_child;

    if(*node == NULL || (*node)->children == NULL)
        return ;
    if( (*node)->children->next == NULL)
    {
        node_child = (*node)->children->content;
        if(node_child->children != NULL && node_child->children->next == NULL)
        {
            node_child_child = node_child->children->content;
            if(node_child_child != NULL && node_child_child->type == AST_SIMPLE_COMMAND ) 
            {

            }
        }
    }
}

t_ast	*ft_ast_subshell(t_token **token)
{
	t_ast	*child_node;

	if (!*token || (*token)->type != TOKEN_PARENS_OPEN)
		return (NULL);
	*token = (*token)->next;
	child_node = ft_ast_andor(token);
	if (!child_node || (*token)->type != TOKEN_PARENS_CLOSE)
		return (ft_ast_free(child_node));
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
		if ((*token)->value == NULL)
			return (ft_ast_free(node));
		ft_lstadd_back(&node->redirect, ft_lstnew(*token));
		*token = (*token)->next;
	}
	return (node);
}

t_ast	*ft_ast_pipeline(t_token **token)
{
	t_token_type	token_type;
	t_ast			*node_parent;
	t_ast			*node_child;
	t_list			*lst;

	if (*token == NULL)
		return (NULL);
	node_child = ft_ast_command(token);
	if (node_child == NULL)
		return (NULL);
	lst = ft_lstnew(node_child);
	node_parent = ft_ast_new(AST_PIPELINE);
	ft_lstadd_back(&node_parent->children, lst);
	while (1)
	{
		token_type = (*token)->type;
		if (token_type == TOKEN_PIPE)
		{
			*token = (*token)->next;
			node_child = ft_ast_command(token);
			if (node_child == NULL)
				return (ft_ast_free(node_parent));
			lst = ft_lstnew(node_child);
			ft_lstadd_back(&node_parent->children, lst);
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
	t_list			*lst;

	if (*token == NULL)
		return (NULL);
	node_child = ft_ast_pipeline(token);
	if (node_child == NULL)
		return (NULL);
	lst = ft_lstnew(node_child);
	node_parent = ft_ast_new(AST_AND_OR);
	ft_lstadd_back(&node_parent->children, lst);
	while (1)
	{
		token_type = (*token)->type;
		if (token_type == TOKEN_OR || token_type == TOKEN_AND)
		{
			lst = ft_lstnew(ft_ast_new(ft_ast_fromtoken(token_type)));
			ft_lstadd_back(&node_parent->children, lst);
			*token = (*token)->next;
			node_child = ft_ast_pipeline(token);
			if (node_child == NULL)
				return (ft_ast_free(node_parent));
			lst = ft_lstnew(node_child);
			ft_lstadd_back(&node_parent->children, lst);
		}
		else
			break ;
	}
	return (node_parent);
}

char	*ft_token_tostr(t_token_type type)
{
	static char *str[20] = {
		"W",
		"||",
		"&&",
		"|",
		"(",
		")",
		"<",
		">",
		">>",
		"<<",
		"newline",
	};
	return (str[type]);
}

t_ast	*parser(t_token *token)
{
	t_ast	*node;
	char	*str;

	if (token == NULL)
		return (NULL);
	node = ft_ast_andor(&token);
	if (token->type != TOKEN_EOI)
		node = ft_ast_free(node);
	if (node == NULL)
	{
		str = ft_token_tostr(token->type);
		write(2, "minishell : syntax error near unexpected token `", 48);
		if (token->type == TOKEN_WORD)
			write(2, token->value, token->length);
		else
			write(2, str, ft_strlen(str));
		write(2, "`\n", 2);
	}
	return (node);
}
