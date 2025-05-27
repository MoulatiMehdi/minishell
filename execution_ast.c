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
	signal(SIGINT, SIG_IGN);
	p = ast->children;
	status = 0;
	while (p)
	{
		child = p->content;
		if (child->type == AST_SIMPLE_COMMAND)
			status = ft_execute_simplecommand(child);
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
