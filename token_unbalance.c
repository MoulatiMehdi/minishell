/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_unbalance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:00:02 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/18 11:45:32 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_init.h"

int	ft_str_isoperator(const char *str)
{
	size_t				i;
	static const char	*operators[] = {">>", "<<", "||", "&&", 0};

	i = 0;
	while (operators[i])
	{
		if (strncmp(str, operators[i], 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

static char	ft_unbalanced_find(const char *str)
{
	long	count_parens;
	size_t	i;
	char	c;

	i = 0;
	count_parens = 0;
	while (str[i])
	{
		c = str[i];
		count_parens += (c == '(') - (c == ')');
		/*if (str[i] == '(' && str[i + 1] == ')')*/
		/*	return (' ');*/
		if (count_parens < 0)
			return ('(');
		if (c == '"' || c == '\'')
		{
			i++;
			while (str[i] && str[i] != c)
				i++;
			if (str[i] != c)
				return (c);
		}
		i++;
	}
	return ((count_parens != 0) * '(');
}

int	is_unbalance(const char *str)
{
	char	c;

	c = ft_unbalanced_find(str);
	if (c == '(' || c == ')')
		write(2, "Syntax error : unbalanced parentheses\n", 38);
	if (c == '"')
		write(2, "Syntax error : unbalanced double quotes\n", 40);
	if (c == '\'')
		write(2, "Syntax error : unbalanced single quotes\n", 40);
	/*if (c == ' ')*/
	/*	write(2, "Syntax error : empty parentheses\n", 33);*/
	return (c != '\0');
}
