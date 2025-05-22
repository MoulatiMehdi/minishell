/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:36:09 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/22 19:43:03 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "execution.h"
#include "libft/libft.h"
#include "parser.h"
#include "status.h"
#include "tokenizer.h"
#include <signal.h>

t_ast	*ft_ast_simplecommand(t_token **token);

void	ft_shell_execute(char *str)
{
	t_token			*token;
	t_ast			*node;
	unsigned char	exit_code;

	if (str == NULL)
		return ;
	token = tokenize(str);
	if (token && token->type == TOKEN_EOI)
		return ;
	lexer(token);
	node = ft_ast_pipeline(&token);
	if (*ft_sigint_recieved())
	{
		exit_code = SIGINT + 128;
		*ft_sigint_recieved() = 0;
	}
	else if (node == NULL)
		exit_code = 2;
	else
		exit_code = ft_execute_pipeline(node);
	ft_status_set(exit_code);
	return ;
}

void	ft_shell_interactive(void)
{
	char			*str;
	unsigned char	status;

	rl_outstream = stderr;
	while (1)
	{
		ft_signal_parent();
		str = readline(SHELL_PROMPT);
		if (str == NULL)
			break ;
		signal(SIGINT, SIG_IGN);
		ft_shell_execute(str);
		status = ft_status_get() - 128;
		if (status == SIGINT || status == SIGQUIT)
			write(2, "\n", 1);
		if (*str)
			add_history(str);
		free(str);
		ft_clear();
	}
	rl_clear_history();
	write(2, "\nexit\n", 6);
	return ;
}

void	ft_shell_noninteractive(void)
{
	char			*str;
	unsigned char	exit_code;

	exit_code = 0;
	while (1)
	{
		signal(SIGINT, SIG_DFL);
		str = readline(NULL);
		if (str == NULL)
			break ;
		ft_collector_track(str);
		ft_shell_execute(str);
		ft_clear();
	}
	return ;
}
