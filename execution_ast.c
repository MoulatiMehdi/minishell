/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:37:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/25 11:06:49 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "expansion.h"
#include "libft/libft.h"
#include "parser.h"
#include "env.h"

int ft_execute_pipeline(t_ast *ast)
{
	return (0);
}

static void ft_subshell_child(t_ast *ast, t_ast *child)
{
	ft_signal_child();
	ft_env_set(ft_copy_env(ft_env_get()));
	if (ft_redirect(ast->redirect))
		ft_status_exit(1);
	ft_status_exit(ft_execute_andor(child));
}

int ft_execute_subshell(t_ast *ast)
{
	pid_t pid;
	int status;

	if (!ast || !ast->children)
		return (0);
	pid = fork();
	if (pid < 0)
		return (perror(SHELL_NAME ": fork"), 1);
	if (pid == 0)
		ft_subshell_child(ast, ast->children->content);
	ft_signal_parent();
	waitpid(pid, &status, 0);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (WTERMSIG(wstatus) + 128);
	if (WIFSTOPPED(wstatus))
		return (WSTOPSIG(wstatus) + 128);
	return (status);
}

void ft_ast_expand(t_ast *ast)
{
	if (!ast)
		return;
	ft_lstiter(ast->args, (void (*)(void *))expand_token);
	ft_lstiter(ast->redirect, (void (*)(void *))expand_token);
}

int ft_execute_simplecommand(t_ast *ast)
{
	char **args;
	int status;

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

int ft_execute_andor(t_ast *ast)
{
	t_list *p;
	t_ast *child;
	int status;

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
