/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_buildin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:37:11 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/16 18:37:12 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_command_isbuildin(char *str)
{
	size_t		i;
	static char	*buildins[] = {"echo", "env", "pwd", "unset", "export", "cd",
		"exit", NULL};

	i = 0;
	while (buildins[i])
	{
		if (ft_strcmp(buildins[i], str) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_execute_buildin(t_list *redirect, char **args)
{
	size_t	i;
	int		status;
	int		fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	status = ft_redirect(redirect);
	if (status)
		return (status);
	i = 1;
	while (args[i])
	{
		printf("%s\n", args[i]);
		i++;
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
