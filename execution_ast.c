/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:37:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/27 09:26:11 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "execution.h"
#include "expansion.h"
#include "libft/libft.h"
#include "parser.h"

int	ft_execute_pipeline(t_ast *ast)
{
	t_pipe_ctx	ctx;

	ctx.in_fd = -1;
	ctx.last_pid = 0;
	run_pipeline(ast, &ctx);
	return (wait_for_all(ctx.last_pid));
}

int	ft_execute_subshell(t_ast *ast)
{
	pid_t	pid;
	int		status;

	if (!ast || !ast->children)
		return (0);
	pid = fork();
	if (pid < 0)
		return (perror(SHELL_NAME ": fork"), 1);
	if (pid == 0)
	{
		ft_signal_child();
		if (ft_redirect(ast->redirect))
			ft_status_exit(1);
		ft_status_exit(ft_execute_andor(ast));
	}
	ft_signal_parent();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	if (WIFSTOPPED(status))
		return (WSTOPSIG(status) + 128);
	return (status);
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

int	ft_execute_andor(t_ast *ast)
{
	t_list	*p;
	t_ast	*child;
	int		status;

	if (ast == NULL)
		return (0);
	p = ast->children;
	status = 0;
	while (p)
	{
		child = p->content;
		if (child->type == AST_SIMPLE_COMMAND)
			status = ft_execute_simplecommand(child);
		else if (child->type == AST_SUBSHELL)
			status = ft_execute_subshell(child);
		else if (child->type == AST_PIPELINE)
			status = ft_execute_pipeline(child);
		else if (child->type == AST_OR && status == 0)
			p = ft_ast_nextchildwithtype(p, AST_AND);
		else if (child->type == AST_AND && status != 0)
			p = ft_ast_nextchildwithtype(p, AST_OR);
		if (p)
			p = p->next;
	}
	return (status);
}
