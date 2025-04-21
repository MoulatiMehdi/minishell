/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:55:36 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/21 18:21:37 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "tokenizer.h"

void	lexer(t_token *head)
{
	while (head && head->type != TOKEN_EOI)
	{
		head->type = TOKEN_WORD;
		if (ft_strncmp("||", head->value, head->length) == 0)
			head->type = TOKEN_OR;
		else if (ft_strncmp("&&", head->value, head->length) == 0)
			head->type = TOKEN_AND;
		else if (ft_strncmp("<<", head->value, head->length) == 0)
			head->type = TOKEN_REDIRECT_HERE;
		else if (ft_strncmp(">>", head->value, head->length) == 0)
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
		head = head->next;
	}
}
