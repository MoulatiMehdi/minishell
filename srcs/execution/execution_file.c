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
#include <sys/stat.h>
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
	}
	if (ft_execute(redirect, path, args) < 0)
		return (1);
	waitpid(-1, &wstatus, 0);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (WTERMSIG(wstatus) + 128);
	if (WIFSTOPPED(wstatus))
		return (WSTOPSIG(wstatus) + 128);
	return (0);
}

void	ft_execute_ast(t_ast *child, t_list **p, int *status)
{
	if (child->type == AST_SIMPLE_COMMAND)
		*status = ft_execute_simplecommand(child);
	else if (child->type == AST_SUBSHELL)
		*status = ft_execute_subshell(child);
	else if (child->type == AST_PIPELINE)
		*status = ft_execute_pipeline(child);
	else if (child->type == AST_OR && *status == 0)
		*p = ft_ast_nextchildwithtype(*p, AST_AND);
	else if (child->type == AST_AND && *status != 0)
		*p = ft_ast_nextchildwithtype(*p, AST_OR);
}
