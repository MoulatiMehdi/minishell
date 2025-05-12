/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:06:52 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/12 11:32:21 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int echo_cmd(t_cmd *cmd)
{
	int i = 0;
	int j = 0;
	int new_line = 1;
	if (!cmd)
		return 1;
	//! need to be removed later
	if (strcmp(cmd->name, "echo") != 0)
		return 127;

	while (cmd->args && cmd->args[j] && ft_strncmp(cmd->args[j], "-n", 2) == 0)
	{
		int k = 2;
		while (cmd->args[j][k] == 'n')
			k++;
		if (cmd->args[j][k] != '\0')
			break;
		new_line = 0;
		j++;
	}
	cmd->args = &cmd->args[j];

	while (cmd->args && cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
	return 0;
}
