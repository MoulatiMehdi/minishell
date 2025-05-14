/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:01:54 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/14 15:13:07 by okhourss         ###   ########.fr       */
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
		ft_putendl_fd(curr->content, 1);
		curr = curr->next;
	}
}

int	env_cmd(t_cmd *cmd)
{
	if (!cmd || !cmd->env)
		return (1);
	if (cmd->args && cmd->args[0])
	{
		ft_putendl_fd("env: too many arguments", 2);
		return (1);
	}
	print_env(cmd->env);
	return (0);
}
