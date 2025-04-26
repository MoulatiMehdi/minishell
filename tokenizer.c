/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:23:41 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/19 18:00:46 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_init.h"

static void	ft_token_expansion(t_token **token_curr, const char *line,
		size_t *i)
{
	if (*token_curr == NULL)
		*token_curr = ft_token_new(&line[*i], 0);
	(*token_curr)->length++;
	(*i)++;
	if (!ft_isalpha(line[*i]) && line[*i] != '_')
		return ;
	(*i)++;
	(*token_curr)->length++;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
	{
		(*i)++;
		(*token_curr)->length++;
	}
}

static void	ft_token_quote(t_token **token_curr, const char *line, size_t *i)
{
	char	c;

	if (!*token_curr)
		*token_curr = ft_token_new(&line[*i], 0);
	c = line[*i];
	while (line[*i])
	{
		(*token_curr)->length++;
		(*i)++;
		if (line[*i] == c)
			break ;
	}
	(*i)++;
	(*token_curr)->length++;
}

static int	ft_token_operator(t_token **token_head, t_token **token_curr,
		const char *line, size_t *i)
{
	int			len;
	const char	*str;

	len = 0;
	str = &line[*i];
	if (ft_str_isoperator(str))
		len = 2;
	else if (ft_char_isoperator(str[0]) && str[0] != '&')
		len = 1;
	if (len > 0)
	{
		if (*token_curr)
			ft_token_push(token_head, *token_curr);
		if (str[0] == '<' || str[0] == '>')
			str = NULL;
		ft_token_push(token_head, ft_token_new(str, (str != NULL) * len));
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
