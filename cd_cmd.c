/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:20:00 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/15 13:35:59 by okhourss         ###   ########.fr       */
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

static int	validate_args(t_cmd *cmd, char **target)
{
	if (cmd->args[0] && cmd->args[1])
	{
		if (ft_putendl_fd("cd: too many arguments", 2) < 0)
			perror("cd");
		return (1);
	}
	if (!cmd->args[0])
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
		*target = cmd->args[0];
	return (0);
}

static int	update_directory(const char *target, t_array *env)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
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
	free(oldpwd);
	set_env_var(env, "PWD", newpwd);
	free(newpwd);
	return (0);
}

int	cd_cmd(t_cmd *cmd)
{
	char	*target;

	if (!cmd || !cmd->env)
		return (1);
	if (validate_args(cmd, &target))
		return (1);
	return (update_directory(target, cmd->env));
}
