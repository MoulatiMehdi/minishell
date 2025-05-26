/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:38:59 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/15 15:39:00 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parser.h"
#include "tokenizer.h"
#include "word.h"
#include <string.h>
#include <unistd.h>

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

void	ft_token_print(t_token *token)
{
	if (token == NULL || token->type == TOKEN_EOI)
		ft_putstr_fd("newline", 2);
	else if (token->type == TOKEN_OR)
		ft_putstr_fd("||", 2);
	else if (token->type == TOKEN_AND)
		ft_putstr_fd("&&", 2);
	else if (token->type == TOKEN_PIPE)
		ft_putstr_fd("|", 2);
	else if (token->type == TOKEN_PARENS_OPEN)
		ft_putstr_fd("(", 2);
	else if (token->type == TOKEN_PARENS_CLOSE)
		ft_putstr_fd(")", 2);
	else if (token->type == TOKEN_REDIRECT_IN)
		ft_putstr_fd("<", 2);
	else if (token->type == TOKEN_REDIRECT_OUT)
		ft_putstr_fd(">", 2);
	else if (token->type == TOKEN_REDIRECT_APPEND)
		ft_putstr_fd(">>", 2);
	else if (token->type == TOKEN_REDIRECT_HERE)
		ft_putstr_fd("<<", 2);
	else if (token->type == TOKEN_WORD && token->value)
		write(2, token->value, token->length);
}

t_ast	*parser(t_token *token)
{
	t_ast	*node;

	if (token == NULL)
		return (NULL);
	node = ft_ast_andor(&token);
	if (*ft_sigint_recieved())
		return (NULL);
	if (token->type != TOKEN_EOI || node == NULL)
	{
		node = NULL;
		write(2, "minishell : syntax error near unexpected token `", 48);
		ft_token_print(token);
		write(2, "`\n", 2);
	}
	return (node);
}
