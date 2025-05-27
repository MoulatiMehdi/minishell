/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:37:19 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/27 09:15:22 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "execution.h"
#include "libft/libft.h"
#include <sys/wait.h>
#include <unistd.h>

int	ft_execute(t_list *redirect, char *pathname, char **args)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror(SHELL_NAME ": fork");
	if (pid != 0)
		return (pid);
	ft_command_execute(redirect, pathname, args);
	return (pid);
}

int	ft_execute_file(t_list *redirect, char **args)
{
	char	*path;
	int		wstatus;

	path = NULL;
	if (args && args[0])
	{
		if (ft_strchr(args[0], '/'))
			path = args[0];
		else
			path = ft_command_search(args[0]);
		if (ft_execute(redirect, path, args) < 0)
			return (1);
		waitpid(-1, &wstatus, 0);
		if (WIFEXITED(wstatus))
			return (WEXITSTATUS(wstatus));
		if (WIFSIGNALED(wstatus))
			return (WTERMSIG(wstatus) + 128);
		if (WIFSTOPPED(wstatus))
			return (WSTOPSIG(wstatus) + 128);
	}
	return (0);
}
