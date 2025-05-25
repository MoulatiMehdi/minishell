/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:38:34 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/25 17:10:18 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "execution.h"
#include "libft/libft.h"
#include "parser.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#define NAME_LENGTH 8
#define HEREDOC_FILENAME_PREFIX "/tmp/sh-"
#define ERR_HERE_PRE "bash: warning: here-document delimited by eof (wanted `"
#define ERR_HERE_SUF "')\n"
#define HEREDOC_HASHKEY "sZqvKFughoCVnmYrpjHxWLGtJUbfdQiywBAxMPzIkTeDSclENROasV"

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

int	ft_heredoc_eoferror(char *line, t_token *token)
{
	if (line)
		return (0);
	ft_putstr_fd(ERR_HERE_PRE, 2);
	write(2, token->value, token->length);
	ft_putstr_fd(ERR_HERE_SUF, 2);
	return (1);
}

char	*ft_heredoc(t_token *token, char *delimiter)
{
	char	*txt;
	char	*line;

	*ft_sigint_recieved() = 0;
	rl_getc_function = ft_getc;
	txt = NULL;
	signal(SIGINT, ft_sigint_heredoc);
	while (1)
	{
		if (ft_shell_isinteractive())
			line = readline("> ");
		else
			line = readline("");
		if (*ft_sigint_recieved() || ft_heredoc_eoferror(line, token))
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		ft_strconcat(&txt, line);
		ft_strconcat(&txt, "\n");
		free(line);
	}
	free(line);
	rl_getc_function = rl_getc;
	signal(SIGINT, SIG_IGN);
	return (txt);
}

void	ft_heredoc_generatename(char name[100])
{
	int					i;
	int					len;
	static const char	table[] = HEREDOC_HASHKEY;
	static size_t		counter = 0;

	i = 0;
	len = ft_strlen(HEREDOC_FILENAME_PREFIX);
	ft_memcpy(name, HEREDOC_FILENAME_PREFIX, len);
	while (i < NAME_LENGTH)
	{
		name[len + i] = table[(counter + i * 7) % (sizeof(table) - 1)];
		i++;
	}
	name[len + i] = '\0';
	counter = (counter + 1) % sizeof(table);
}

int	ft_heredoc_tempfile(char *str)
{
	int		fd[2];
	char	name[100];

	if (str)
	{
		ft_heredoc_generatename(name);
		fd[1] = open(name, O_RDWR | O_CREAT | O_EXCL, 0600);
		ft_putstr_fd(str, fd[1]);
		fd[0] = open(name, O_RDONLY);
		close(fd[1]);
		unlink(name);
	}
	else
		fd[0] = open("/dev/null", O_RDONLY);
	return (fd[0]);
}
