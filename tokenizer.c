/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:23:41 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/19 11:42:55 by mmoulati         ###   ########.fr       */
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
		else if (ft_char_isoperator(char_prev))
		{
			if (ft_str_isoperator(token_curr->value))
			{
				token_curr->length++;
				i++;
				char_curr = line[i];
				continue ;
			}
			else
			{
				ft_token_push(&token_head, token_curr);
				token_curr = NULL;
			}
		}
		if (ft_char_isquote(char_curr))
		{
			ft_token_quote(&token_curr, &line[i]);
		}
		else if (ft_char_isdollar(char_curr))
		{
			ft_token_expansion(&token_curr, &line[i]);
		}
		else if (ft_char_isoperator(char_curr))
		{
			ft_token_push(&token_head, token_curr);
			token_curr = ft_token_new(&line[i + token_curr->length], 1);
		}
		else if (ft_char_isblank(char_curr))
		{
			ft_token_push(&token_head, token_curr);
			token_curr = NULL;
			i++;
			continue ;
		}
		else if (token_curr == NULL)
			token_curr = ft_token_new(&line[i], 1);
		else
			token_curr->length++;
		if (token_curr)
			i += token_curr->length;
		char_curr = line[i];
	}
	return (token_head);
}
