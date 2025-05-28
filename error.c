/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:37:05 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/28 10:36:28 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "execution.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>

void	ft_perror(char *name, char *msg)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	len;

	len = ft_strlen(SHELL_NAME);
	len1 = ft_strlen(name);
	len2 = ft_strlen(msg);
	str = malloc(len + len1 + len2 + 6UL);
	if (!str)
		return ;
	ft_memcpy(str, SHELL_NAME, len);
	ft_memcpy(&str[len], ": ", 2);
	len += 2;
	ft_memcpy(&str[len], name, len1);
	len += len1;
	ft_memcpy(&str[len], ": ", 2);
	len += 2;
	ft_memcpy(&str[len], msg, len2);
	len += len2;
	str[len] = '\n';
	len++;
	str[len] = '\0';
	write(2, str, len);
	free(str);
}

void	ft_token_error(t_token *token, char *msg)
{
	char	*str;

	str = ft_strndup(token->value, token->length);
	ft_perror(str, msg);
	free(str);
}
