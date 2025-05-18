/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 09:43:55 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/17 09:43:56 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_redirect_dup(char *filename, t_token_type type)
{
	int	fd;
	int	fd_dup;

	fd = -1;
	fd_dup = STDOUT_FILENO;
	if (type == TOKEN_REDIRECT_IN)
	{
		fd = open(filename, O_RDONLY);
		fd_dup = STDIN_FILENO;
	}
	if (type == TOKEN_REDIRECT_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (type == TOKEN_REDIRECT_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (type == TOKEN_REDIRECT_HERE)
	{
		fd = ft_heredoc_tempfile(filename);
		fd_dup = STDIN_FILENO;
	}
	if (fd >= 0)
	{
		dup2(fd, fd_dup);
		close(fd);
	}
	return (fd);
}

int	ft_redirect(t_list *redirect)
{
	t_token	*token;

	while (redirect)
	{
		token = redirect->content;
		if (token->fields == NULL || token->fields->length != 1)
		{
			ft_token_error(token, "ambigious redirection");
			return (1);
		}
		if (ft_redirect_dup(token->fields->head->content, token->type) < 0)
		{
			ft_token_error(token, strerror(errno));
			return (1);
		}
		redirect = redirect->next;
	}
	return (0);
}
