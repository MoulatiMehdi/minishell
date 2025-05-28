/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:20:00 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/28 12:48:19 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	validate_args(char **args, char **target)
{
	if (args[0] && args[1])
	{
		if (ft_putendl_fd(SHELL_NAME ": cd: too many arguments", 2) < 0)
			perror(SHELL_NAME ": cd");
		return (1);
	}
	if (!args[0])
	{
		*target = getenv("HOME");
		if (!*target)
		{
			if (ft_putendl_fd(SHELL_NAME ": cd: HOME not set", 2) < 0)
				perror(SHELL_NAME ": cd");
			return (1);
		}
	}
	else
		*target = args[0];
	return (0);
}

static char	*fetch_oldpwd(void)
{
	char	*pwd;
	char	*oldpwd;

	pwd = ft_env_getvalue("PWD");
	if (pwd)
		oldpwd = ft_strdup(pwd);
	else
		oldpwd = NULL;
	return (oldpwd);
}

static int	update_directory(const char *target)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = fetch_oldpwd();
	if (chdir(target) != 0)
	{
		perror(SHELL_NAME": cd");
		free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror(SHELL_NAME": cd");
		free(oldpwd);
		return (1);
	}
	ft_env_set("OLDPWD", oldpwd);
	ft_env_set("PWD", newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}

int	cd_cmd(char **args)
{
	char	*target;

	if (validate_args(args, &target))
		return (1);
	return (update_directory(target));
}
