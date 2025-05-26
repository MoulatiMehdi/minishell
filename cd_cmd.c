/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:20:00 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/26 11:55:22 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	set_env_var(t_array *env, const char *key, const char *val)
{
	t_list	*node;
	char	*kv;
	char	*nv;

	node = ft_get_env((char *)key, env);
	kv = ft_strjoin((char *)key, "=");
	nv = ft_strjoin(kv, val);
	free(kv);
	if (node)
	{
		free(node->content);
		node->content = nv;
	}
	else
		ft_array_push(&env, nv);
}

static int	validate_args(char **args, char **target)
{
	if (args[0] && args[1])
	{
		if (ft_putendl_fd("cd: too many arguments", 2) < 0)
			perror("cd");
		return (1);
	}
	if (!args[0])
	{
		*target = getenv("HOME");
		if (!*target)
		{
			if (ft_putendl_fd("cd: HOME not set", 2) < 0)
				perror("cd");
			return (1);
		}
	}
	else
		*target = args[0];
	return (0);
}

static char	*fetch_oldpwd(t_array *env)
{
	char	*pwd;
	char	*oldpwd;

	pwd = get_env_var(env, "PWD");
	if (pwd)
		oldpwd = strdup(pwd);
	else
		oldpwd = NULL;
	return (oldpwd);
}

static int	update_directory(const char *target, t_array *env)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = fetch_oldpwd(env);
	if (!oldpwd || chdir(target) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	set_env_var(env, "OLDPWD", oldpwd);
	set_env_var(env, "PWD", newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}

int	cd_cmd(char **args)
{
	char	*target;
	t_array	*env;

	env = ft_env_get();
	if (!env)
		return (1);
	if (validate_args(args, &target))
		return (1);
	return (update_directory(target, env));
}
