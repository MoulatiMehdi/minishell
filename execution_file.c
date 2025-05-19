/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:37:19 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/16 18:37:20 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "execution.h"
#include "libft/libft.h"
#include "parser.h"
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	ft_command_ispathfound(char *dir, char *name, char *path[2])
{
	path[0] = ft_path_join(dir, name);
	if (ft_path_isfile(path[0]))
	{
		if (access(path[0], X_OK) == 0)
		{
			free(path[1]);
			path[1] = path[0];
			return (1);
		}
		else if (!path[1])
			path[1] = path[0];
	}
	if (path[1] != path[0])
		free(path[0]);
	return (0);
}

char	*ft_command_search(char *name)
{
	char	*path[2];
	char	**strs;
	size_t	i;

	i = 0;
	path[1] = NULL;
	strs = ft_path_get();
	if (strs == NULL)
		return (NULL);
	while (strs[i])
	{
		if (ft_command_ispathfound(strs[i++], name, path))
			break ;
	}
	ft_split_free(&strs);
	ft_collector_track(path[1]);
	return (path[1]);
}

int	ft_execute(t_list *redirect, char *pathname, char **args)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror(SHELL_NAME ": fork");
	if (pid == 0)
	{
		ft_signal_init();
		if (ft_redirect(redirect))
			ft_execute_exit(1);
		if (!pathname)
		{
			ft_perror(args[0], "command not found");
			ft_execute_exit(127);
		}
		execve(pathname, args, NULL);
		if (ft_path_isdir(pathname))
			ft_perror(pathname, strerror(EISDIR));
		else
			ft_perror(pathname, strerror(errno));
		ft_execute_exit(126);
	}
	return (pid);
}

int	ft_execute_file(t_list *redirect, char **args)
{
	char	*path;
	int		wstatus;

	path = NULL;
	if (args)
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
