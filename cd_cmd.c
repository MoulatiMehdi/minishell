/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:20:00 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/14 14:53:21 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void set_env_var(t_array *env, const char *key, const char *val)
{
    t_list *node;
    char    *kv;
    char    *new;

    node = ft_get_env((char *)key, env);
    kv   = ft_strjoin((char *)key, "=");
    new  = ft_strjoin(kv, val);
    free(kv);
    if (node)
    {
        free(node->content);
        node->content = new;
    }
    else
        ft_array_push(&env, new);
}

int cd_cmd(t_cmd *cmd)
{
    char *oldpwd;
    char *newpwd;
    char *target;

    if (!cmd || !cmd->env)
        return (1);
    if (cmd->args[0] && cmd->args[1])
    {
        ft_putendl_fd("cd: too many arguments", 2);
        return (1);
    }
    if (!cmd->args[0])
    {
        target = getenv("HOME");
		printf("home target -> %s\n", target);
        if (!target)
        {
            ft_putendl_fd("cd: HOME not set", 2);
            return (1);
        }
    }
    else
        target = cmd->args[0];
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
    {
        perror("cd");
        return (1);
    }
    if (chdir(target) != 0)
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
    set_env_var(cmd->env, "OLDPWD", oldpwd);
    free(oldpwd);
    set_env_var(cmd->env, "PWD", newpwd);
    free(newpwd);
    return (0);
}

