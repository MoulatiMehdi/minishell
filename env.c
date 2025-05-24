/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:22:59 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/24 13:19:35 by okhourss         ###   ########.fr       */
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

t_array	*ft_env_set(t_array *new_env)
{
	t_array	**ptr;

	ptr = ft_env_ptr();
	*ptr = new_env;
	return (new_env);
}

t_array *ft_init_env(char **env)
{
	size_t i;
	t_array *env_arr;

	if (!env)
		return (NULL);
	i = 0;
	env_arr = ft_array_new();
	while (env[i])
	{
		ft_array_push(&env_arr, ft_strdup(env[i]));
		i++;
	}
	ft_env_set(env_arr);
	return(env);
}