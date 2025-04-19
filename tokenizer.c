/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:23:41 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/19 13:04:59 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "char.h"
#include "libft/libft.h"
#include "tokenizer.h"

void	ft_token_expansion(t_token **token, const char *str)
{
	size_t	i;

	i = 0;
	if (!ft_char_isdollar(str[0]))
		return ;
	i++;
	if (*token == NULL)
		*token = ft_token_new(str, 0);
	(*token)->length++;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return ;
	i++;
	(*token)->length++;
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		i++;
		(*token)->length++;
	}
	return ;
}

void	ft_token_quote(t_token **token, const char *str)
{
	size_t	i;
	char	char_curr;

	i = 0;
	if (!ft_char_isquote(str[0]))
		return ;
	if (*token == NULL)
		*token = ft_token_new(str, 0);
	char_curr = str[i];
	while (str[i])
	{
		i++;
		if (str[i] == char_curr)
			break ;
	}
	i++;
	(*token)->length += i;
}

void	ft_token_operator(t_token **token, const char *str)
{
	size_t	i;
	char	char_curr;

	i = 0;
}

t_token	*tokenize(const char *line)
{
	t_token	*token_head;
	t_token	*token_curr;
	char	char_curr;
	size_t	i;

	if (is_unbalance(line))
		return (NULL);
	i = 0;
	token_curr = NULL;
	token_head = NULL;
	while (1)
	{
		if (line[i] == '\0')
		{
			if (token_curr)
				ft_token_push(&token_head, token_curr);
			ft_token_addeoi(&token_head);
			break ;
		}
		if (ft_str_isoperator(&line[i]))
		{
			if (token_curr)
				ft_token_push(&token_head, token_curr);
			ft_token_push(&token_head, ft_token_new(&line[i], 2));
			token_curr = NULL;
			i += 2;
			continue ;
		}
		if (ft_char_isoperator(line[i]) && line[i] != '&')
		{
			if (token_curr)
				ft_token_push(&token_head, token_curr);
			ft_token_push(&token_head, ft_token_new(&line[i], 1));
			token_curr = NULL;
			i++;
			continue ;
		}
		if (ft_char_isquote(line[i]))
		{
			if (!token_curr)
				token_curr = ft_token_new(&line[i], 0);
			while (line[i])
			{
				token_curr->length++;
				i++;
				if (ft_char_isquote(line[i]))
					break ;
			}
			i++;
			continue ;
		}
		if (ft_char_isdollar(line[i]))
		{
			if (token_curr == NULL)
				token_curr = ft_token_new(&line[i], 0);
			token_curr->length++;
			i++;
			if (!ft_isalpha(line[i]) && line[i] != '_')
				continue ;
			i++;
			(token_curr)->length++;
			while (ft_isalnum(line[i]) || line[i] == '_')
			{
				i++;
				(token_curr)->length++;
			}
			continue ;
		}
		if (ft_char_isblank(line[i]))
		{
			if (token_curr)
				ft_token_push(&token_head, token_curr);
			token_curr = NULL;
			while (ft_char_isblank(line[i]))
				i++;
			continue ;
		}
		if (!token_curr)
			token_curr = ft_token_new(&line[i], 0);
		token_curr->length++;
		i++;
	}
	return (token_head);
}
