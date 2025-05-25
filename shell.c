/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:36:09 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/25 16:47:40 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "execution.h"
#include "libft/libft.h"
#include "parser.h"
#include "status.h"
#include "tokenizer.h"
#include <signal.h>

int		ft_execute_andor(t_ast *ast);

void	ft_shell_execute(char *str)
{
	t_token			*token;
	t_ast			*node;
	unsigned char	exit_code;

	if (str == NULL)
		return ;
	token = tokenize(str);
	if (!token || token->type == TOKEN_EOI)
		return ;
	lexer(token);
	node = parser(token);
	if (*ft_sigint_recieved())
	{
		exit_code = SIGINT + 128;
		*ft_sigint_recieved() = 0;
	}
	else if (node == NULL)
		exit_code = 2;
	else
	{
		exit_code = ft_execute_andor(node);
		if (exit_code == 128 + SIGINT || exit_code == SIGQUIT + 128)
			write(2, "\n", 1);
	}
	ft_status_set(exit_code);
}

void	ft_shell_interactive(void)
{
	char	*str;

	rl_outstream = stderr;
	while (1)
	{
		ft_signal_parent();
		str = readline(SHELL_PROMPT);
		if (str == NULL)
			break ;
		if (*str)
			add_history(str);
		signal(SIGINT, SIG_IGN);
		ft_shell_execute(str);
		free(str);
		ft_clear();
	}
	rl_clear_history();
	write(2, "exit\n", 6);
	return ;
}

void	ft_shell_noninteractive(void)
{
	char	*str;

	while (1)
	{
		signal(SIGINT, ft_sigint_noiteractive);
		str = readline(NULL);
		if (str == NULL)
			break ;
		ft_collector_track(str);
		ft_shell_execute(str);
		ft_clear();
	}
	return ;
}

bool	ft_shell_isinteractive(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDERR_FILENO));
}
