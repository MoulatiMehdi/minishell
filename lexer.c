/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:55:36 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/22 08:06:03 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "tokenizer.h"
#include <stdio.h>
#include <unistd.h>

void	ft_lexer_type(t_token *const head)
{
	if (head->type == TOKEN_EOI)
		return ;
	if (ft_strncmp("||", head->value, 2) == 0)
		head->type = TOKEN_OR;
	else if (ft_strncmp("&&", head->value, 2) == 0)
		head->type = TOKEN_AND;
	if (ft_strncmp("<<", head->value, 2) == 0)
		head->type = TOKEN_REDIRECT_HERE;
	else if (ft_strncmp(">>", head->value, 2) == 0)
		head->type = TOKEN_REDIRECT_APPEND;
	else if (ft_strncmp("<", head->value, head->length) == 0)
		head->type = TOKEN_REDIRECT_IN;
	else if (ft_strncmp(">", head->value, head->length) == 0)
		head->type = TOKEN_REDIRECT_OUT;
	else if (ft_strncmp("|", head->value, head->length) == 0)
		head->type = TOKEN_PIPE;
	else if (ft_strncmp("(", head->value, head->length) == 0)
		head->type = TOKEN_PARENS_OPEN;
	else if (ft_strncmp(")", head->value, head->length) == 0)
		head->type = TOKEN_PARENS_CLOSE;
	if (head->type != TOKEN_WORD)
	{
		head->length = 0;
		head->value = NULL;
	}
}

void	ft_lexer_recognition(t_token *curr_token)
{
	t_token	*prev_token;
	t_token	*next_token;

	prev_token = NULL;
	next_token = NULL;
	while (curr_token && curr_token->type != TOKEN_EOI)
	{
		ft_lexer_type(curr_token);
		next_token = curr_token->next;
		if (ft_token_isredirect(curr_token->type) && next_token != NULL)
		{
			ft_lexer_type(next_token);
			if (next_token->type == TOKEN_WORD)
			{
				curr_token->length = next_token->length;
				curr_token->value = next_token->value;
				curr_token->next = next_token->next;
				ft_free(next_token);
			}
		}
		prev_token = curr_token;
		curr_token = curr_token->next;
	}
}

int	ft_heredoc_islimit(t_token *token)
{
	size_t	count;

	count = 0;
	while (token && count <= MAX_HEREDOC)
	{
		count += token->length == 2 && ft_strncmp(token->value, "<<", 2) == 0;
		token = token->next;
	}
	return (count > MAX_HEREDOC);
}

void	lexer(t_token *curr_token)
{
	if (ft_heredoc_islimit(curr_token))
	{
		ft_putstr_fd(ERR_HEREDOC_LIMIT, 2);
		ft_status_exit(2);
	}
	ft_lexer_recognition(curr_token);
}
