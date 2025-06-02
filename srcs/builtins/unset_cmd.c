/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:39:54 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/27 10:23:01 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
		ft_array_remove(&env, args[i], (t_func_cmp)ft_keycmp, free);
		i++;
	}
	return (0);
}
