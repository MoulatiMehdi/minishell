/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:46:46 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/26 15:33:10 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft.h"

static void	exec_external(t_ast *cmd, char **args)
{
	char	*path;

	if (ft_redirect(cmd->redirect))
		ft_status_exit(1);
	if (ft_strchr(args[0], '/'))
		path = args[0];
	else
		path = ft_command_search(args[0]);
	if (!path)
	{
		ft_perror(args[0], "command not found");
		ft_status_exit(127);
	}
	execve(path, args, NULL);
	if (ft_path_isdir(path))
		ft_perror(path, strerror(EISDIR));
	else
		ft_perror(path, strerror(errno));
	ft_status_exit(126);
}

static void	exec_segment(t_ast *cmd, int in_fd, int out_fd, t_pipe_ctx *ctx)
{
	pid_t	pid;
	char	**args;

	pid = fork();
	if (pid < 0)
		perror(SHELL_NAME ": fork");
	if (pid == 0)
	{
		ft_signal_child();
		redirect_fds(in_fd, out_fd);
		ft_ast_expand(cmd);
		args = ft_ast_getargs(cmd);
		if (args && ft_command_isbuildin(args[0]))
			exit(ft_execute_buildin(cmd->redirect, args));
		exec_external(cmd, args);
	}
	ctx->last_pid = pid;
}

static void	pipeline_segment(t_ast *cmd, t_pipe_ctx *ctx, int *cmds_left)
{
	int	fds[2];
	int	out_fd;

	out_fd = STDOUT_FILENO;
	if ((*cmds_left)-- > 1)
		if (pipe(fds) < 0)
			perror(SHELL_NAME ": pipe");
	if (*cmds_left >= 1)
		out_fd = fds[1];
	exec_segment(cmd, ctx->in_fd, out_fd, ctx);
	if (ctx->in_fd != STDIN_FILENO)
		close(ctx->in_fd);
	if (out_fd != STDOUT_FILENO)
	{
		close(fds[1]);
		ctx->in_fd = fds[0];
	}
}

static void	run_pipeline(t_ast *ast, t_pipe_ctx *ctx)
{
	t_list	*lst;
	int		cmds_left;
	t_ast	*cmd;

	lst = ast->children;
	cmds_left = ft_lstsize(ast->children);
	while (lst)
	{
		cmd = lst->content;
		pipeline_segment(cmd, ctx, &cmds_left);
		lst = lst->next;
	}
	if (ctx->in_fd != STDIN_FILENO)
		close(ctx->in_fd);
}

int	ft_execute_pipeline(t_ast *ast)
{
	t_pipe_ctx	ctx;

	ctx.in_fd = STDIN_FILENO;
	ctx.last_pid = 0;
	run_pipeline(ast, &ctx);
	return (wait_for_all(ctx.last_pid));
}
