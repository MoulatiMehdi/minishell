/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:06:49 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/27 09:49:13 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft/libft.h"
#include "word.h"

char	*ft_word_type(t_word *word)
{
	if (word->type == WORD_QUOTE_SINGLE)
		return ("WORD_QUOTE_SINGLE");
	else if (word->type == WORD_QUOTE_DOUBLE)
		return ("WORD_QUOTE_DOUBLE");
	else if (word->type == WORD_NONE)
		return ("WORD_NONE");
	else if (word->type == WORD_WILDCARD)
		return ("WORD_WILDCARD");
	else
		return ("WORD_UNKNOWN");
}

void	expand_token(t_token *token)
{
	t_word	*words;
	t_array	*fields;
	char	*str;
	t_word	*tmp;

	words = ft_word_split(token);
	if (!words)
		return ;
	tmp = words;
	while (tmp)
	{
		expand_param(tmp);
		tmp = tmp->next;
	}
	if (token->type != TOKEN_REDIRECT_HERE)
	{
		join_quotes(words);
		fields = field_splitting(words);
		ft_pathname_expansion(token, fields);
		return ;
	}
	str = ft_word_join(words);
	ft_collector_track(str);
	ft_tracked_array_push(&token->fields, str);
}
