/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:23:31 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/06 18:29:14 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	ft_count_word(const char *str, char *charset)
{
	size_t	count;

	if (charset == NULL || str == NULL || str[0] == '\0')
		return (0);
	count = 0;
	while (*str)
	{
		while (*str && ft_strchr(charset, *str) != NULL)
			str++;
		if (!*str)
			break ;
		count++;
		while (*str && ft_strchr(charset, *str) == NULL)
			str++;
	}
	return (count);
}

void	*ft_split_free(char ***strs)
{
	int	i;

	if (strs == NULL || *strs == NULL)
		return (NULL);
	i = 0;
	while ((*strs)[i])
	{
		free((*strs)[i]);
		i++;
	}
	free(*strs);
	*strs = NULL;
	return (NULL);
}

static char	*ft_split_dup(const char **str, char *charset)
{
	size_t	end;
	char	*str_dup;

	end = 0;
	while ((*str)[end] && ft_strchr(charset, (*str)[end]) == NULL)
		end++;
	str_dup = ft_strndup(*str, end);
	*str += end;
	return (str_dup);
}

char	**ft_split(const char *str, char *charset)
{
	char	**strs;
	size_t	size;
	size_t	i;

	if (str == NULL || charset == NULL)
		return (NULL);
	i = 0;
	size = ft_count_word(str, charset);
	strs = (char **)malloc(sizeof(char *) * (size + 1));
	if (!strs)
		return (0);
	while (i < size)
	{
		while (ft_strchr(charset, *str) != NULL)
			str++;
		if (*str == '\0')
			break ;
		strs[i] = ft_split_dup(&str, charset);
		if (strs[i] == NULL)
			return (ft_split_free(&strs));
		i++;
	}
	strs[size] = 0;
	return (strs);
}
