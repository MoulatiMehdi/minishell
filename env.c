/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:22:59 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/23 14:24:20 by okhourss         ###   ########.fr       */
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
