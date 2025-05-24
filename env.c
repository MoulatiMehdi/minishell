/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:14:12 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/24 10:14:12 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*get_env_value(const char *var_name, size_t len)
{
	int			i;
	extern char	**environ;

	if (var_name == NULL || len <= 0)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var_name, len) == 0
			&& environ[i][len] == '=')
			return (&environ[i][len + 1]);
		i++;
	}
	return (NULL);
}
