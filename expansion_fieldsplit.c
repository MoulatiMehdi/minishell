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

int	is_field_splitting_required(t_word *word)
{
	size_t	i;

	i = 0;
	if (!word || word->type != WORD_NONE)
		return (0);
	while (i < word->length)
	{
		if (is_ifs(word->value[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_starting_with_ifs(const char *str)
{
	if (!str || !*str)
		return (0);
	return (is_ifs(*str));
}

int	is_ending_with_ifs(const char *str, size_t len)
{
	if (len == 0)
		return (0);
	return (is_ifs(str[len - 1]));
}

t_array	*field_splitting(t_word *word)
{
	t_array	*fields;
	t_word	*curr;
	t_word	*w;
	size_t	len;
	size_t	i;
	char	*s;
	size_t	start;

	i = 0;
	fields = NULL;
	curr = NULL;
	w = word;
	while (w)
	{
		if (w->type == WORD_QUOTE_SINGLE || w->type == WORD_QUOTE_DOUBLE)
			ft_word_push(&curr, w->type, w->value, w->length);
		else
		{
			s = (char *)w->value;
			len = w->length;
			i = 0;
			start = 0;
			while (i < len)
			{
				if (is_ifs(s[i]))
				{
					if (i > start)
						ft_word_push(&curr, w->type, s + start, i - start);
					if (curr)
					{
						ft_array_push(&fields, curr);
						curr = NULL;
					}
					while (i < len && is_ifs(s[i]))
						i++;
					start = i;
				}
				else
				{
					i++;
				}
			}
			if (start < len)
				ft_word_push(&curr, w->type, s + start, len - start);
		}
		w = w->next;
	}
	if (curr)
		ft_array_push(&fields, curr);
	return (fields);
}
