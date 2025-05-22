/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:15:20 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/18 14:15:21 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word.h"

static size_t	ft_quotelen(const char *str, char c)
{
	size_t	i;

	if (c != '"' && c != '\'')
		return (0);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	ft_word_isquote(t_token *token, size_t index)
{
	return (index < token->length && token->value[index]
		&& !ft_char_isquote(token->value[index]));
}

size_t	ft_word_none(t_word **head, t_token *token, size_t i)
{
	size_t	len;

	len = 0;
	while (ft_word_isquote(token, len + i))
		len++;
	ft_word_push(head, WORD_NONE, &token->value[i], len);
	return (len);
}

size_t	ft_word_quote(t_word **head, t_token *token, size_t i)
{
	size_t		len;
	t_word_type	type;
	char		c;

	c = token->value[i];
	type = (WORD_QUOTE_DOUBLE);
	if (c == '\'')
		type = (WORD_QUOTE_SINGLE);
	len = ft_quotelen(&token->value[i + 1], token->value[i]);
	if (*head == NULL || len > 0)
		ft_word_push(head, type, &token->value[i + 1], len);
	return (len);
}

size_t	ft_word_wildcard(t_word **head, t_token *token, size_t i)
{
	size_t	len;

	len = 0;
	while (token->value[i + len] == '*' && i + len < token->length)
		len++;
	ft_word_push(head, WORD_WILDCARD, &token->value[i], len);
	return (len);
}
