/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:23:41 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/19 16:11:11 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "tokenizer.h"

static void	ft_token_expansion(t_token **token_curr, const char *line,
		size_t *i)
{
	if (*token_curr == NULL)
		*token_curr = ft_token_new(&line[*i], 0);
	(*token_curr)->length++;
	(*i)++;
	if (!ft_isalpha(line[*i]) && line[*i] != '_')
		return ;
	i++;
	(*token_curr)->length++;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
	{
		(*i)++;
		(*token_curr)->length++;
	}
}

static void	ft_token_quote(t_token **token_curr, const char *line, size_t *i)
{
	if (!*token_curr)
		*token_curr = ft_token_new(&line[*i], 0);
	while (line[*i])
	{
		(*token_curr)->length++;
		(*i)++;
		if (ft_char_isquote(line[*i]))
			break ;
	}
	(*i)++;
}

static int	ft_token_operator(t_token **token_head, t_token **token_curr,
		const char *line, size_t *i)
{
	int	len;

	len = 0;
	if (ft_str_isoperator(&line[*i]))
		len = 2;
	else if (ft_char_isoperator(line[*i]) && line[*i] != '&')
		len = 1;
	if (len > 0)
	{
		if (*token_curr)
			ft_token_push(token_head, *token_curr);
		ft_token_push(token_head, ft_token_new(&line[*i], len));
		*token_curr = NULL;
		(*i) += len;
		return (1);
	}
	return (0);
}

static int	ft_token_noword(t_token **token_head, t_token **token_curr,
		const char *line, size_t *i)
{
	if (ft_char_isquote(line[*i]))
	{
		ft_token_quote(token_curr, line, i);
		return (1);
	}
	if (ft_char_isdollar(line[*i]))
	{
		ft_token_expansion(token_curr, line, i);
		return (1);
	}
	if (ft_char_isblank(line[*i]))
	{
		if (*token_curr)
			ft_token_push(token_head, *token_curr);
		*token_curr = NULL;
		while (ft_char_isblank(line[*i]))
			(*i)++;
		return (1);
	}
	return (0);
}

t_token	*tokenize(const char *line)
{
	t_token	*token_head;
	t_token	*token_curr;
	size_t	i;

	if (is_unbalance(line))
		return (NULL);
	i = 0;
	token_curr = NULL;
	token_head = NULL;
	while (1)
	{
		if (line[i] == '\0')
			ft_token_addeoi(&token_head, token_curr);
		if (line[i] == '\0')
			break ;
		if (ft_token_operator(&token_head, &token_curr, line, &i))
			continue ;
		if (ft_token_noword(&token_head, &token_curr, line, &i))
			continue ;
		if (!token_curr)
			token_curr = ft_token_new(&line[i], 0);
		token_curr->length++;
		i++;
	}
	return (token_head);
}
