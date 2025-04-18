/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:55:33 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/18 11:24:12 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&' || c == '('
		|| c == ')');
}

int	is_double_operator(const char *str)
{
	static const char	*ops[] = {">>", "<<", "||", "&&", NULL};
	int					i;

	i = 0;
	while (ops[i])
	{
		if (strncmp(str, ops[i], 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	collect_quoted(const char *line, int i, char quote, const char **start)
{
	int	begin;

	begin = i++;
	while (line[i] && line[i] != quote)
		i++;
	if (!line[i])
		return (-1);
	*start = &line[begin];
	return (i - begin + 1);
}

int	should_start_word(t_state state, char c)
{
	return (state != STATE_WORD && c != ' ' && c != '\t' && !is_operator_char(c)
		&& c != '\'' && c != '"');
}

t_token	*finalize_token(t_tokenizer *t)
{
	if (t->state == STATE_WORD && t->i > t->start)
		t->last = add_token(&t->head, t->last, &t->line[t->start], t->i
				- t->start);
	else if (t->state == STATE_OPERATOR)
		t->last = add_token(&t->head, t->last, &t->line[t->start], 1);
	return (t->head);
}
