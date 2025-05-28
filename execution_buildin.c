/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_buildin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:37:11 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/28 13:54:10 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execution.h"

int	ft_command_isbuildin(char *str)
{
	size_t		i;
	static char	*buildins[] = {"echo", "env", "pwd", "unset", "export", "cd",
		"exit", NULL};

	if (!str)
		return (0);
	i = 0;
	while (buildins[i])
	{
		if (ft_strcmp(buildins[i], str) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_run_builtin(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (echo_cmd(&args[1]));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (cd_cmd(&args[1]));
	else if (ft_strcmp(args[0], "export") == 0)
		return (export_cmd(&args[1]));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (unset_cmd(&args[1]));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (pwd_cmd(&args[1]));
	else if (ft_strcmp(args[0], "env") == 0)
		return (env_cmd(&args[1]));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (exit_cmd(&args[1]));
	return (0);
}

int	ft_execute_buildin(t_list *redirect, char **args)
{
	int	status;
	int	fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	status = ft_redirect(redirect);
	if (status)
		return (status);
	status = ft_run_builtin(args);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);
	return (status);
}
