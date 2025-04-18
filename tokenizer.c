/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:23:41 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/18 12:17:29 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*add_token(t_token **head, t_token *last, const char *start, int len)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->value = start;
	new->length = len;
	new->type = -1;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
		last->next = new;
	return (new);
}

int	handle_quoted_token(t_tokenizer *t)
{
	const char	*quoted;
	int			len;
	char		curr;

	curr = t->line[t->i];
	if (curr != '\'' && curr != '"')
		return (0);
	if (t->state == STATE_WORD)
	{
		t->last = add_token(&t->head, t->last, &t->line[t->start], t->i
				- t->start);
		t->state = STATE_NONE;
	}
	len = collect_quoted(t->line, t->i, curr, &quoted);
	if (len == -1)
	{
		printf("Unclosed quote\n");
		return (-1);
	}
	t->last = add_token(&t->head, t->last, quoted, len);
	t->i += len;
	return (1);
}

int	handle_operator_token(t_tokenizer *t)
{
	if (t->state == STATE_OPERATOR && is_double_operator(&t->line[t->start]))
	{
		t->last = add_token(&t->head, t->last, &t->line[t->start], 2);
		t->i += 1;
		t->state = STATE_NONE;
		return (1);
	}
	if (t->state == STATE_OPERATOR)
	{
		t->last = add_token(&t->head, t->last, &t->line[t->start], 1);
		t->state = STATE_NONE;
		return (1);
	}
	if (is_operator_char(t->line[t->i]))
	{
		if (t->state == STATE_WORD)
			t->last = add_token(&t->head, t->last, &t->line[t->start], t->i
					- t->start);
		t->start = t->i++;
		t->state = STATE_OPERATOR;
		return (1);
	}
	return (0);
}

int	handle_whitespace_token(t_tokenizer *t)
{
	if (t->line[t->i] == ' ' || t->line[t->i] == '\t')
	{
		if (t->state == STATE_WORD)
			t->last = add_token(&t->head, t->last, &t->line[t->start], t->i
					- t->start);
		t->i++;
		t->state = STATE_NONE;
		return (1);
	}
	return (0);
}

t_token	*tokenize(const char *line)
{
	t_tokenizer	t;
	char		c;
	int			quote_status;

	c = ft_unbalanced_find(line);
	if (c)
		return (ft_error_unbalance(c));
	init_token(&t, line);
	while (t.line[t.i])
	{
		c = t.line[t.i];
		if (handle_operator_token(&t) || handle_whitespace_token(&t))
			continue ;
		quote_status = handle_quoted_token(&t);
		if (quote_status == -1)
			return (NULL);
		if (quote_status == 1)
			continue ;
		if (should_start_word(t.state, c))
		{
			t.start = t.i;
			t.state = STATE_WORD;
		}
		t.i++;
	}
	return (finalize_token(&t));
}
