/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quotejoin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:01:07 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/24 18:33:00 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft/libft.h"

int	is_joinable(t_word *word)
{
	size_t	i;

	if (!word)
		return (0);
	if (word->type == WORD_QUOTE_DOUBLE || word->type == WORD_QUOTE_SINGLE)
		return (1);
	i = 0;
	while (i < word->length)
	{
		if (ft_strchr(IFS "*", word->value[i]))
			return (0);
		i++;
	}
	return (1);
}

void	join_quotes(t_word *head)
{
	t_word	*curr;
	t_word	*next;

	curr = head;
    while (curr && curr->next)
	{
		next = curr->next;
		if (is_joinable(curr) && is_joinable(next))
		{
			curr->value = ft_strjoin_track((char *)curr->value, next->value);
			curr->length = ft_strlen(curr->value);
			curr->type = WORD_QUOTE_SINGLE;
			curr->next = next->next;
			ft_free(next);
		}
		else
			curr = curr->next;
	}
}
