/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_fieldsplit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:00:47 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/24 10:38:01 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "word.h"

int	is_ifs(char c)
{
	return (c == '\n' || c == '\t' || c == ' ');
}

void	ft_field_push(t_word *w, t_word **curr, t_array **fields)
{
	size_t	len;
	size_t	i;
	size_t	start;

	len = w->length;
	i = 0;
	start = 0;
	while (i < len)
	{
		if (is_ifs(w->value[i]))
		{
			if (i > start)
				ft_word_push(curr, w->type, w->value + start, i - start);
			if (curr)
				ft_array_push(fields, curr);
			curr = NULL;
			while (i < len && is_ifs(w->value[i]))
				i++;
			start = i;
		}
		else
			i++;
	}
	if (start < len)
		ft_word_push(curr, w->type, w->value + start, len - start);
}

t_array	*field_splitting(t_word *word)
{
	t_array	*fields;
	t_word	*curr;
	t_word	*w;

	fields = NULL;
	curr = NULL;
	w = word;
	while (w)
	{
		if (w->type == WORD_QUOTE_SINGLE || w->type == WORD_QUOTE_DOUBLE)
			ft_word_push(&curr, w->type, w->value, w->length);
		else
			ft_field_push(w, &curr, &fields);
		w = w->next;
	}
	if (curr)
		ft_array_push(&fields, curr);
	return (fields);
}
