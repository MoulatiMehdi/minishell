/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:30:18 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/12 13:01:44 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int pwd_cmd(t_cmd *cmd)
{
	if (!cmd)
		return 1;
	char *pwd;
	if (ft_strncmp(cmd->name, "pwd", 3) != 0)
		return 1;
	pwd = getcwd(NULL,0);
	if (!pwd)
	{
		perror("pwd");
		return 1;
	}
	ft_putendl_fd(pwd,1);
	free(pwd);
	return 0;
}