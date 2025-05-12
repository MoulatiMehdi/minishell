/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:01:54 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/12 13:21:51 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void print_env(char **env)
{
	int i = 0;
	if (!env)
		return;
	while (env[i])
	{
		ft_putendl_fd(env[i],1);
		i++;
	}
}

int env_cmd(t_cmd *cmd)
{
	if (!cmd)
		return 1;
	if (ft_strncmp(cmd->name,"env",3) != 0)
		return 1;
	print_env(cmd->args);
	return 0;
}