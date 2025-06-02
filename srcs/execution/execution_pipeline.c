/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:46:46 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/27 08:57:24 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parser.h"
#include "status.h"

static void	exec_external(t_ast *cmd)
{
	char	*path;
	char	**args;

	args = NULL;
	path = NULL;
	ft_signal_child();
	args = ft_ast_getargs(cmd);
	if (args && ft_command_isbuildin(args[0]))
		ft_status_exit(ft_execute_buildin(cmd->redirect, args));
	else
	{
		if (args && args[0])
		{
			if (ft_strchr(args[0], '/'))
				path = args[0];
			else
				path = ft_command_search(args[0]);
		}
		ft_command_execute(cmd->redirect, path, args);
	}
}

static void	exec_segment(t_ast *cmd, int out_fd, int fds[2], t_pipe_ctx *ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror(SHELL_NAME ": fork");
	if (pid == 0)
	{
		redirect_fds(ctx->in_fd, out_fd);
		if (fds[0] >= 0)
			close(fds[0]);
		if (fds[1] >= 0)
			close(fds[1]);
		ft_ast_expand(cmd);
		if (cmd->type == AST_SIMPLE_COMMAND)
			exec_external(cmd);
		else if (cmd->type == AST_SUBSHELL)
		{
			ft_signal_parent();
			ft_status_exit(ft_execute_andor(cmd));
		}
	}
	ctx->last_pid = pid;
}

static void	pipeline_segment(t_ast *cmd, t_pipe_ctx *ctx, int *cmds_left)
{
	int	fds[2];
	int	out_fd;

	fds[0] = -1;
	fds[1] = -1;
	out_fd = -1;
	if ((*cmds_left)-- > 1)
	{
		if (pipe(fds) < 0)
			perror(SHELL_NAME ": pipe");
	}
	if (*cmds_left >= 1)
		out_fd = fds[1];
	exec_segment(cmd, out_fd, fds, ctx);
	if (ctx->in_fd >= 0)
		close(ctx->in_fd);
	if (out_fd >= 0)
	{
		if (fds[1] >= 0)
			close(fds[1]);
		ctx->in_fd = fds[0];
	}
	else
		ctx->in_fd = -1;
}

void	run_pipeline(t_ast *ast, t_pipe_ctx *ctx)
{
	t_list	*lst;
	int		cmds_left;
	t_ast	*cmd;

	lst = ast->children;
	cmds_left = count_cmds(ast);
	while (lst)
	{
		cmd = lst->content;
		pipeline_segment(cmd, ctx, &cmds_left);
		lst = lst->next;
	}
	if (ctx->in_fd >= 0)
		close(ctx->in_fd);
}
