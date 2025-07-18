/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipeline_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 11:37:14 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/26 17:08:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	count_cmds(t_ast *ast)
{
	t_list	*lst;
	int		n;

	n = 0;
	lst = ast->children;
	while (lst)
	{
		n++;
		lst = lst->next;
	}
	return (n);
}

void	redirect_fds(int in_fd, int out_fd)
{
	if (in_fd >= 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd >= 0)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

int	wait_for_all(pid_t last_pid)
{
	pid_t	wait_pid;
	int		status;
	int		exit_status;

	exit_status = 0;
	while (1)
	{
		wait_pid = wait(&status);
		if (wait_pid <= 0)
			break ;
		if (wait_pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = WTERMSIG(status) + 128;
			else if (WIFSTOPPED(status))
				exit_status = WSTOPSIG(status) + 128;
		}
	}
	return (exit_status);
}
