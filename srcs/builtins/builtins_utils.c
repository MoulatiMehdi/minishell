/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:31:52 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/28 10:38:19 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_var_key(char *var)
{
	int		i;
	char	*key;

	if (!var)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	key = malloc(i + 1);
	if (!key)
		return (NULL);
	ft_memcpy(key, var, i);
	key[i] = '\0';
	return (key);
}

void	compute_limit(int sign, unsigned long *limit)
{
	if (sign >= 0)
		*limit = (unsigned long)LONG_MAX;
	else
		*limit = (unsigned long)LONG_MAX + 1UL;
}
