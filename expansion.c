/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:06:49 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/25 13:09:51 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft/libft.h"
#include "word.h"
#include <stdio.h>
#include <unistd.h>

void	expand_token(t_token *token)
{
	t_word	*words;
	t_word	*tmp;
	t_array	*fields;
	char	*str;

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
	ft_array_push(&token->fields, str);
}
