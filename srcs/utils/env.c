/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:22:59 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/27 14:48:29 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

t_array	**ft_env_ptr(void)
{
	static t_array	*env = NULL;

	return (&env);
}

t_array	*ft_env_get(void)
{
	return (*ft_env_ptr());
}

t_array	*ft_env_init(char **env)
{
	size_t	i;
	t_array	**env_arr;

	env_arr = ft_env_ptr();
	i = 0;
	while (env && env[i])
	{
		ft_array_push(env_arr, ft_strdup(env[i]));
		i++;
	}
	ft_check_env_fundamentals(env_arr);
	return (*env_arr);
}

char	**ft_env_strs(void)
{
	t_array	*array;
	char	**strs;
	t_list	*lst;
	size_t	i;

	array = ft_env_get();
	if (!array || array->length == 0)
		return (NULL);
	strs = malloc((sizeof(char *) + 1) * array->length);
	lst = array->head;
	i = 0;
	while (lst)
	{
		strs[i] = lst->content;
		lst = lst->next;
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

void	ft_env_clear(void)
{
	ft_array_destroy(ft_env_ptr(), free);
	*ft_env_ptr() = NULL;
}
