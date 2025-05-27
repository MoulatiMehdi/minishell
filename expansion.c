/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:06:49 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/27 11:12:34 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft/libft.h"
#include "word.h"
#include <unistd.h>

char * ft_word_type(t_word * word)
{
    if(word->type == WORD_QUOTE_SINGLE)
        return "WORD_QUOTE_SINGLE";
    else  if(word->type == WORD_QUOTE_DOUBLE)
            return "WORD_QUOTE_DOUBLE";
    else  if(word->type == WORD_NONE)
            return "WORD_NONE";
    else  if(word->type == WORD_WILDCARD)
            return "WORD_WILDCARD";
    else 
        return "WORD_UNKNOWN";

}
void ft_word_print(t_word * tmp)
{
    while (tmp)
	{
        printf("- %s %s\n",ft_word_type(tmp),ft_strndup_track(tmp->value,tmp->length));
		tmp = tmp->next;
	}
}

void	expand_token(t_token *token)
{
	t_word	*words;
	t_array	*fields;
	char	*str;
    t_word * tmp;
	words = ft_word_split(token);
    printf("splitting : \n");
    ft_word_print(words);
	if (!words)
		return ;
	tmp = words;
	while (tmp)
	{
		expand_param(tmp);
		tmp = tmp->next;
	}
    printf("expan params : \n");
    ft_word_print(words);
	if (token->type != TOKEN_REDIRECT_HERE)
	{
		join_quotes(words);
        printf("quote join : \n");
		ft_word_print(words);
        fields = field_splitting(words);
		ft_pathname_expansion(token, fields);
		return ;
	}
	str = ft_word_join(words);
	ft_collector_track(str);
	ft_tracked_array_push(&token->fields, str);
}
