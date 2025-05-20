/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:36:09 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/16 18:36:10 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	node = ft_ast_simplecommand(&token);
	if (*ft_sigint_recieved())
		exit_code = SIGINT + 128;
	else if (node == NULL)
		exit_code = 2;
	else
		exit_code = ft_execute_simplecommand(node);
	ft_status_set(exit_code);
	return ;
}

void	ft_shell_interactive(void)
{
	char			*str;
	unsigned char	exit_code;

	exit_code = 0;
	rl_outstream = stderr;
	while (1)
	{
		ft_signal_bashignore();
		str = readline(SHELL_PROMPT);
		if (str == NULL)
			break ;
		ft_shell_execute(str);
		if (*str)
			add_history(str);
		free(str);
		ft_clear();
	}
	rl_clear_history();
	write(2, "exit\n", 5);
	return ;
}

void	ft_shell_noninteractive(void)
{
	char			*str;
	unsigned char	exit_code;

	exit_code = 0;
	while (1)
	{
		ft_signal_noninteractive();
		str = readline("");
		if (str == NULL)
			break ;
		ft_collector_track(str);
		ft_shell_execute(str);
		ft_clear();
	}
	return ;
}
