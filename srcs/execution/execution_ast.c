/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:37:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/28 18:41:23 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "execution.h"
#include "expansion.h"
#include "libft.h"
#include "parser.h"
#include "status.h"
#include <stdio.h>

int	ft_execute_pipeline(t_ast *ast)
{
	t_pipe_ctx	ctx;

	ctx.in_fd = -1;
	ctx.last_pid = 0;
	run_pipeline(ast, &ctx);
	return (wait_for_all(ctx.last_pid));
}

void	ft_ast_expand(t_ast *ast)
{
	if (!ast)
		return ;
	ft_lstiter(ast->args, (void (*)(void *))expand_token);
	ft_lstiter(ast->redirect, (void (*)(void *))expand_token);
}

int	ft_execute_simplecommand(t_ast *ast)
{
	char	**args;
	int		status;

	if (ast == NULL)
		return (0);
	status = 0;
	ft_ast_expand(ast);
	args = ft_ast_getargs(ast);
	if (args && ft_command_isbuildin(args[0]))
		status = ft_execute_buildin(ast->redirect, args);
	else
		status = ft_execute_file(ast->redirect, args);
	return (status);
}

int	ft_execute_subshell(t_ast *ast)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid < 0)
		return (perror(SHELL_NAME ": fork: "), 1);
	if (pid == 0)
	{
		ft_signal_child();
		signal(SIGINT, SIG_IGN);
		ft_ast_expand(ast);
		if (ft_redirect(ast->redirect))
			ft_status_exit(1);
		ft_status_exit(ft_execute_andor(ast));
	}
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (WTERMSIG(wstatus) + 128);
	if (WIFSTOPPED(wstatus))
		return (WSTOPSIG(wstatus) + 128);
	return (wstatus);
}

int	ft_execute_andor(t_ast *ast)
{
	t_list	*p;
	int		status;

	if (ast == NULL)
		return (0);
	p = ast->children;
	status = 0;
	while (p)
	{
		ft_execute_ast((t_ast *)p->content, &p, &status);
		ft_status_set(status);
		if (p)
			p = p->next;
	}
	return (status);
}
