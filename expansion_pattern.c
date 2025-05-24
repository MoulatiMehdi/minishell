/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_pattern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:01:00 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/24 12:01:08 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "expansion.h"
#include "libft/libft.h"
#include <stddef.h>

static int	ft_pattern_ismatch(char *pattern, char *path, char *mask);

static char	*ft_strnmatch(char *src, char *to_find, size_t n)
{
	size_t	i;

	if (src == NULL || to_find == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		if (ft_strncmp(&src[i], to_find, n) == 0)
			return (&src[i]);
		i++;
	}
	return (NULL);
}

static int	ft_pattern_wildcard(char *pattern, char *mask, char *path)
{
	char	*ptr;
	size_t	len;
	size_t	j;

	len = 0;
	j = 0;
	while (mask[len] == '0')
		len++;
	ptr = pattern;
	while (1)
	{
		ptr = ft_strnmatch(&path[j], ptr, len);
		if (!ptr)
			return (0);
		if (ft_pattern_ismatch(&pattern[len], &ptr[len], &mask[len]))
			return (1);
		j += len;
	}
	return (0);
}

static int	ft_pattern_ismatch(char *pattern, char *path, char *mask)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (pattern[0] == '\0' && path[0] != '\0')
		return (0);
	while (pattern[i])
	{
		if (mask[i] == '1')
		{
			while (mask[i] == '1')
				i++;
			if (!pattern[i])
				return (1);
			return (ft_pattern_wildcard(&pattern[i], &mask[i], &path[j]));
		}
		else if (pattern[i] != path[j])
			return (0);
		i++;
		j++;
	}
	return (1);
}

t_list	*ft_pattern_matchall(char *word, char *mask, char *path[2])
{
	t_list	*head;
	DIR		*stream_dir;
	char	*name;

	head = NULL;
	stream_dir = ft_diren_open(path[0]);
	if (path[1])
		path[1][0] = '\0';
	while (1)
	{
		name = ft_diren_getname(stream_dir);
		if (!name)
			break ;
		if ((path[1] && !ft_path_isdir(name)) || (mask[0] == '1'
				&& name[0] == '.'))
			continue ;
		if (ft_pattern_ismatch(word, name, mask))
			ft_lstadd_back(&head, ft_lstnew(ft_strjoin(path[0], name)));
	}
	closedir(stream_dir);
	if (path[1])
		path[1][0] = '/';
	if (path[1])
		ft_list_strconcat(head, "/");
	return (head);
}
