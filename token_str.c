/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:20:44 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/19 16:20:45 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

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
