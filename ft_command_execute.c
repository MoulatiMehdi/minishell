/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:58:54 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/27 11:11:19 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "execution.h"
#include "status.h"

int	ft_command_ispathfound(char *dir, char *name, char *path[2])
{
	if (!name || !dir)
		return (0);
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

	if (name == NULL)
		return (NULL);
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

void	ft_command_execute(t_list *redirect, char *pathname, char **args)
{
	char	**envp;

	envp = NULL;
	ft_signal_child();
	if (ft_redirect(redirect))
		ft_status_exit(1);
	if (!args || !args[0])
		ft_status_exit(0);
	if (!pathname)
	{
		ft_perror(args[0], "command not found");
		ft_status_exit(127);
	}
	envp = ft_env_strs();
	execve(pathname, args, envp);
	free(envp);
	if (ft_path_isdir(pathname))
		ft_perror(pathname, strerror(EISDIR));
	else
		ft_perror(pathname, strerror(errno));
	ft_status_exit(126);
}
