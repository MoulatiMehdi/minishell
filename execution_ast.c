/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:37:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/22 19:42:16 by okhourss         ###   ########.fr       */
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

static int	count_cmds(t_ast *ast)
{
	t_list	*lst;
	int		n;

	lst = ast->children;
	n = 0;
	while (lst)
	{
		if (((t_ast *)lst->content)->type != TOKEN_PIPE)
			n++;
		lst = lst->next;
	}
	return (n);
}

static void	collect_cmds(t_ast *ast, t_ast **cmds)
{
	t_list	*lst;
	int		i;
	t_ast	*node;

	lst = ast->children;
	i = 0;
	while (lst)
	{
		node = lst->content;
		if (node->type != TOKEN_PIPE)
			cmds[i++] = node;
		lst = lst->next;
	}
}

static void	make_pipes(int *fds, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pipe(&fds[2 * i]) < 0)
			perror(SHELL_NAME ": pipe");
		i++;
	}
}

static void	close_pipes(int *fds, int n)
{
	int	i;

	i = 0;
	while (i < 2 * n)
		close(fds[i++]);
}

static int	exec_segment(t_ast *cmd, int *fds, int idx, int ncmds)
{
	pid_t	pid;
	char	**args;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
		perror(SHELL_NAME ": fork");
	if (pid == 0)
	{
		ft_signal_child();
		if (idx > 0)
			dup2(fds[2 * (idx - 1)], STDIN_FILENO);
		if (idx < ncmds - 1)
			dup2(fds[2 * idx + 1], STDOUT_FILENO);
		close_pipes(fds, ncmds - 1);
		ft_ast_expand(cmd);
		args = ft_ast_getargs(cmd);
		if (args && ft_command_isbuildin(args[0]))
			status = ft_execute_buildin(cmd->redirect, args);
		else
			ft_exec_external(cmd, args);
		exit(status);
	}
	return (pid);
}
		// waitpid(l_pid, &status, 0);


int	ft_execute_pipeline(t_ast *ast)
{
	int		ncmds;
	ncmds = count_cmds(ast);
	t_ast	*cmds[ncmds];
	int		fds[2 * (ncmds - 1)];
	pid_t	l_pid;
	int		i;
	int	status;
	int	last;

	collect_cmds(ast, cmds);
	make_pipes(fds, ncmds - 1);
	i = 0;
	while (i < ncmds)
	{
		l_pid = exec_segment(cmds[i], fds, i, ncmds);
		i++;
	}
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		last = WEXITSTATUS(status);
	close_pipes(fds, ncmds - 1);
	return (last);
}
