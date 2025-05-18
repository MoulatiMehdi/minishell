/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:24:36 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/18 15:24:37 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenizer_init.h"

char	*ft_heredoc_quote_removal(t_token *token)
{
	t_word	*word;
	char	*delimiter;

	word = ft_word_split(token);
	delimiter = ft_word_join(word);
	ft_collector_track(delimiter);
	return (delimiter);
}

int	ft_heredoc_isquote(t_token *token)
{
	size_t	i;

	if (token == NULL || token->value == NULL)
		return (0);
	i = 0;
	while (i < token->length)
	{
		if (ft_char_isquote(token->value[i]))
			return (1);
		i++;
	}
	return (0);
}

t_ast	*ft_ast_redirect(t_token **token, t_ast *node)
{
	char	*str;

	if ((*token)->value == NULL)
	{
		*token = (*token)->next;
		return (NULL);
	}
	ft_lstadd_back(&node->redirect, ft_lstnew((*token)));
	if ((*token)->type != TOKEN_REDIRECT_HERE)
		return (node);
	str = ft_heredoc((*token), ft_heredoc_quote_removal(*token));
	if (*ft_sigint_recieved())
	{
		while ((*token)->type != TOKEN_EOI)
			*token = (*token)->next;
		return (NULL);
	}
	if (ft_heredoc_isquote(*token))
		(*token)->value = NULL;
	if ((*token)->value == NULL)
		ft_array_push(&(*token)->fields, str);
	else
		(*token)->value = str;
	(*token)->length = ft_strlen((*token)->value);
	return (node);
}
