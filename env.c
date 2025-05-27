/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:22:59 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/27 06:44:26 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static t_array	**ft_env_ptr(void)
{
	static t_array	*env = NULL;

	return (&env);
}

t_array	*ft_env_get(void)
{
	return (*ft_env_ptr());
}

t_array	*ft_init_env(char **env)
{
	size_t	i;
	t_array	**env_arr;

	if (!env)
		return (NULL);
	env_arr = ft_env_ptr();
	i = 0;
	while (env[i])
	{
		ft_array_push(env_arr, ft_strdup(env[i]));
		i++;
	}
	return (*env_arr);
}
