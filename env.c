/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:22:59 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/26 15:00:02 by okhourss         ###   ########.fr       */
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
	env_arr = NULL;
	i = 0;
	while (env[i])
	{
		ft_array_push(&env_arr, ft_strdup(env[i]));
		i++;
	}
	ft_env_set(env_arr);
	return(ft_env_get());
}

t_array *ft_copy_env(t_array *env)
{
    t_array *new_env;
    t_list *node;

	new_env = NULL;
    if (!env)
        return (NULL);
    node = env->head;
    while (node)
    {
        ft_array_push(&new_env, ft_strdup((char *)node->content));
        node = node->next;
    }
    return (new_env);
}