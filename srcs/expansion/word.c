/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:30:58 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/18 13:30:59 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word.h"

t_word	*ft_word_new(t_word_type type, const char *value, size_t length)
{
	t_word	*word;

	word = ft_malloc(sizeof(t_word));
	if (word == NULL)
		return (NULL);
	word->type = type;
	word->value = value;
	word->next = NULL;
	word->length = length;
	return (word);
}

t_word	*ft_word_push(t_word **head, t_word_type type, const char *value,
		size_t length)
{
	t_word	*p;
	t_word	*elem;

	if (head == NULL)
		return (NULL);
	elem = ft_word_new(type, value, length);
	if (elem == NULL)
		return (NULL);
	if (*head == NULL)
		return (*head = elem);
	p = *head;
	while (p->next)
		p = p->next;
	return (p->next = elem);
}

char	*ft_word_mask(t_word *word)
{
	char	*mask;
	size_t	i;
	size_t	total;

	mask = ft_word_join(word);
	total = 0;
	while (word)
	{
		i = 0;
		while (i < word->length)
		{
			mask[total] = '0';
			mask[total] += word->type == WORD_NONE && word->value[i] == '*';
			i++;
			total++;
		}
		word = word->next;
	}
	return (mask);
}
