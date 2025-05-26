/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:39:54 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/26 18:53:28 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_strcmp_key(const char *key, const char *content)
{
	size_t	i;

	i = 0;
	while (key[i] && content[i] && content[i] != '=')
	{
		if (key[i] != content[i])
			return (key[i] - content[i]);
		i++;
	}
	if (key[i] == '\0' && content[i] == '=')
		return (0);
	return (key[i] - content[i]);
}

int	unset_cmd(char **args)
{
	int		i;
	t_array	*env;

	env = ft_env_get();
	if (!args || !args[0])
	{
		return (0);
	}
	i = 0;
	while (args[i])
	{
		ft_array_remove(&env, args[i], ft_strcmp_key, free);
		i++;
	}
	return (0);
}
