/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:29:26 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/13 13:45:59 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void ft_update_pwd_env(t_array *env){
	char *new_pwd = getcwd(NULL,0);
	if (!new_pwd)
		return;
	t_list *var;
	var = ft_get_env("PWD",env);
	if (var != NULL)
	{
		var->content = ft_strjoin("PWD=",new_pwd);
		free(new_pwd);
	}
	return;
}

int cd_cmd(t_cmd *cmd)
{
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
	ft_update_pwd_env(cmd->env);
	return 0;
}