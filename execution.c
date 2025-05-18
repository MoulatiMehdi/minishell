/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:37:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/16 18:37:18 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_execute_andor(t_ast *ast)
{
	if (ast == NULL)
		return (0);
	return (0);
}

void	ft_ast_expand(t_ast *ast)
{
	t_list	*p;

	if (!ast)
		return ;
	p = ast->args;
	while (p)
	{
		ft_token_expand(p->content);
		p = p->next;
	}
	p = ast->redirect;
	while (p)
	{
		ft_token_expand(p->content);
		p = p->next;
	}
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
