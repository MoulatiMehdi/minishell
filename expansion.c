/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:06:49 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/25 10:36:21 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft/libft.h"
#include "word.h"
#include <stdio.h>
#include <unistd.h>

void	ft_word_print(t_word *word, char *label)
{
	printf("\n*************************\n%s\n", label);
	while (word)
	{
		write(1, "- ", 2);
		write(1, word->value, word->length);
		write(1, "\n", 1);
		word = word->next;
	}
}

void	print(void *p)
{
	t_word	*word;

	word = p;
	while (word)
	{
		printf("\033[31m{\033[0m%s\033[31m}\033[0m -> ", word->value);
		word = word->next;
	}
	printf("(NULL)\n");
}

void	expand_token(t_token *token)
{
	t_word	*words;
	t_word	*tmp;
	t_array	*fields;

	words = ft_word_split(token);
	if (!words)
		return ;
	tmp = words;
	while (tmp)
	{
		expand_param(tmp);
		tmp = tmp->next;
	}
	join_quotes(words);
	fields = field_splitting(words);
	if (fields)
		ft_lstiter(fields->head, print);
	ft_pathname_expansion(token, fields);
}
