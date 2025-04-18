/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:23:41 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/18 18:47:11 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char.h"
#include "libft/libft.h"
#include "tokenizer.h"

void	ft_token_name(t_token **token, const char *str)
{
	size_t	i;

	i = 0;
	if (*token == NULL)
		*token = ft_token_new(str, 1);
	i++;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return ;
	i++;
	(*token)->length++;
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		(*token)->length++;
		i++;
	}
	return ;
}

t_token	*tokenize(const char *line)
{
	size_t	i;
	t_token	*token_head;
	t_token	*token_curr;
	char	char_prev;
	char	char_curr;

	i = 0;
	char_curr = '\0';
	token_head = NULL;
	token_curr = NULL;
	if (is_unbalance(line))
		return (NULL);
	while (1)
	{
		char_prev = char_curr;
		char_curr = line[i];
		if (ft_char_iseoi(char_curr))
		{
			if (token_curr != NULL)
				ft_token_push(&token_head, token_curr);
			ft_token_addeoi(&token_head);
			break ;
		}
		if (ft_char_isoperator(char_prev))
		{
			if (ft_str_isoperator(token_curr->value))
			{
				token_curr->length++;
				continue ;
			}
			ft_token_push(&token_head, token_curr);
			token_curr = NULL;
		}
		if (ft_char_isquote(char_curr))
		{
			while (line[i])
			{
				token_curr->length++;
				i++;
				if (line[i] == char_curr)
					break ;
			}
			i++;
			token_curr->length++;
			continue ;
		}
		if (ft_char_isdollar(char_curr))
		{
			ft_token_name(&token_curr, &line[i]);
			continue ;
		}
		if (ft_char_isoperator(char_curr))
		{
			ft_token_push(&token_head, token_curr);
			i++;
			token_curr = ft_token_new(&line[i], 1);
			i++;
			continue ;
		}
		if (ft_char_isblank(char_curr))
		{
			ft_token_push(&token_head, token_curr);
			token_curr = NULL;
			i++;
			continue ;
		}
		token_curr = ft_token_new(&line[i], 1);
	}
	return (token_head);
}
