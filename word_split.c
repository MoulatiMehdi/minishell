/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:31:10 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/18 13:31:11 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "tokenizer_init.h"
#include "word.h"

t_word	*ft_word_split(t_token *token)
{
	size_t	i;
	t_word	*head;

	if (token == NULL || token->value == NULL || token->length == 0)
		return (NULL);
	i = 0;
	head = NULL;
	while (i < token->length)
	{
		if (ft_char_isquote(token->value[i]))
			i += 2 + ft_word_quote(&head, token, i);
		else
			i += ft_word_none(&head, token, i);
	}
	return (head);
}

char	*ft_word_join(t_word *word)
{
	char	*str;

	str = NULL;
	while (word)
	{
		ft_strnconcat(&str, word->value, word->length);
		word = word->next;
	}
	return (str);
}
