/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:38:34 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/15 15:38:35 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t	*ft_sigint_recieved(void)
{
	static volatile sig_atomic_t	received = 0;

	return (&received);
}

int	ft_getc(FILE *stream)
{
	char	c;

	(void)stream;
	if (*ft_sigint_recieved())
		return (EOF);
	if (read(STDIN_FILENO, &c, 1) <= 0)
		return (EOF);
	return (c);
}

char	*ft_heredoc(t_token *token)
{
	char	*txt;
	char	*line;

	*ft_sigint_recieved() = 0;
	rl_getc_function = ft_getc;
	txt = NULL;
	while (1)
	{
		line = readline("> ");
		if (*ft_sigint_recieved())
			break ;
		if (!line)
			break ;
		if (ft_strncmp(line, token->value, token->length) == 0
			&& line[token->length] == '\0')
		{
			free(line);
			break ;
		}
		ft_strconcat(&txt, line);
		free(line);
	}
	rl_getc_function = rl_getc;
	return (txt);
}
