/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balance.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:00:02 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/18 11:45:32 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	is_balanced(char *str)
{
	long	count_parens;
	size_t	i;
	char	c;

	i = 0;
	count_parens = 0;
	while (str[i])
	{
		c = str[i];
		count_parens += (c == '(');
		count_parens -= (c == ')');
		if (count_parens < 0)
			return (0);
		if (c == '"' || c == '\'')
		{
			i++;
			while (str[i] && str[i] != c)
				i++;
			if (str[i] != c)
				return (0);
		}
		i++;
	}
	return (count_parens == 0);
}
