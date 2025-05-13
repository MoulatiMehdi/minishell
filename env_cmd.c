/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:01:54 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/13 11:14:01 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void print_env(t_array *env)
{
	if (!env)
		return;
	t_list *curr;
	curr = env->head;
	while (curr)
	{
		ft_putendl_fd(curr->content,1);
		curr = curr->next;
	}
}

int env_cmd(t_cmd *cmd)
{
	if (!cmd)
		return 1;
	if (ft_strncmp(cmd->name,"env",3) != 0)
		return 1;
	print_env(cmd->env);
	return 0;
}