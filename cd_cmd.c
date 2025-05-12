/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:29:26 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/12 18:10:08 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int cd_cmd(t_cmd *cmd)
{
	int i = 0;

	if (!cmd)
		return (1);
	if (!cmd->args[0])
	{
		ft_putendl_fd("cd: usage: cd <directory>", 2);
		return 1;
	}
	if (cmd->args[1])
	{
		ft_putendl_fd("cd: too many arguments",2);
		return 1;
	}
	if (chdir(cmd->args[0]) != 0)
	{
		perror("cd");
		return 1;
	}
	//TODO need to update the PWD
	return 0;
}