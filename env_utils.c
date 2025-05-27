/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:48:12 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/27 14:49:16 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	ft_add_env_fundamentals(int shlvl, int oldpwd, int pwd)
{
	char	*curr_pwd;

	if (shlvl)
		ft_env_set("SHLVL", "1");
	if (oldpwd)
		ft_env_set("OLDPWD", "");
	if (pwd)
	{
		curr_pwd = getcwd(NULL, 0);
		ft_env_set("PWD", curr_pwd);
		free(curr_pwd);
	}
}

void	ft_check_env_fundamentals(t_array **env)
{
	char	*shlvl;

	if (!env)
		return (ft_add_env_fundamentals(1, 1, 1));
	if (ft_env_getvalue("PWD") == NULL)
		ft_add_env_fundamentals(0, 0, 1);
	if (ft_env_getvalue("OLDPWD") == NULL)
		ft_add_env_fundamentals(0, 1, 0);
	shlvl = ft_env_getvalue("SHLVL");
	if (shlvl == NULL)
		ft_add_env_fundamentals(1, 0, 0);
	else
	{
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
		ft_env_set("SHLVL", shlvl);
		free(shlvl);
	}
}
