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

#include "libft/libft.h"
#include <fcntl.h>
#include <readline/readline.h>
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

void	ft_heredoc_eoferror(t_token *token)
{
	ft_putstr_fd(ERR_HERE_PRE, 2);
	write(2, token->value, token->length);
	ft_putstr_fd(ERR_HERE_SUF, 2);
}

char	*ft_heredoc(t_token *token, char *delimiter)
{
	char	*txt;
	char	*line;

	*ft_sigint_recieved() = 0;
	rl_getc_function = ft_getc;
	txt = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_heredoc_eoferror(token);
			break ;
		}
		if (*ft_sigint_recieved() || ft_strcmp(line, delimiter) == 0)
			break ;
		ft_strconcat(&txt, line);
		ft_strconcat(&txt, "\n");
		free(line);
	}
	free(line);
	rl_getc_function = rl_getc;
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

	ft_heredoc_generatename(name);
	fd[1] = open(name, O_RDWR | O_CREAT | O_EXCL, 0600);
	ft_putstr_fd(str, fd[1]);
	fd[0] = open(name, O_RDONLY);
	close(fd[1]);
	unlink(name);
	return (fd[0]);
}
