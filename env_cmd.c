/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:01:54 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/26 17:36:12 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_env(t_array *env)
{
	t_list	*curr;

	if (!env)
		return ;
	curr = env->head;
	while (curr)
	{
		if (ft_putendl_fd((char *)curr->content, 1) < 0)
		{
			perror(SHELL_NAME "env: write error");
			break ;
		}
		curr = curr->next;
	}
}

int	env_cmd(char **args)
{
	t_array	*env;

	env = ft_env_get();
	if (!env)
		return (1);
	if (args && args[0])
	{
		ft_putendl_fd(SHELL_NAME "env: too many arguments", 2);
		return (1);
	}
	print_env(env);
	return (0);
}
