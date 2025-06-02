/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_pathname.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:00:55 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/27 09:44:31 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "expansion.h"
#include "libft/libft.h"
#include "word.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_pathname_dirname(char *word, char *mask)
{
	size_t	len;
	size_t	slash;
	int		found;

	len = 0;
	slash = 0;
	found = 0;
	if (word == NULL || mask == NULL)
		return (NULL);
	while (word[len])
	{
		if (word[len] == '/')
		{
			slash = len;
			found = 1;
		}
		if (word[len] == '*' && mask[len] == '1')
		{
			if (!found)
				break ;
			return (ft_strndup(word, slash + 1));
		}
		len++;
	}
	return (NULL);
}

int	ft_pathname_isvalid(char *word, char *mask, char *prefix)
{
	int		is_slash;
	int		wild;
	size_t	i;

	if (!ft_path_iscurrentdir(prefix))
		return (0);
	is_slash = 0;
	wild = 0;
	i = 0;
	while (word[i])
	{
		if (wild && is_slash)
			return (0);
		if (mask[i] == '1')
			wild++;
		if (wild && word[i] == '/')
		{
			is_slash = 1;
			while (word[i] == '/')
				i++;
			continue ;
		}
		i++;
	}
	return (wild != 0);
}

size_t	ft_pathname_lastslash(char *word, char *mask)
{
	size_t	idx;
	size_t	slash_idx;

	idx = 0;
	slash_idx = 0;
	while (word[idx] && mask[idx] == '0')
	{
		if (word[idx] == '/')
			slash_idx = idx + 1;
		idx++;
	}
	return (slash_idx);
}

t_list	*ft_pathname_files(t_word *words)
{
	size_t	idx;
	t_list	*head;
	char	*path[2];
	char	*word[2];

	if (words == NULL)
		return (NULL);
	word[0] = ft_word_join(words);
	word[1] = ft_word_mask(words);
	path[0] = ft_pathname_dirname(word[0], word[1]);
	head = NULL;
	if (word[0] && ft_pathname_isvalid(word[0], word[1], path[0]))
	{
		idx = ft_pathname_lastslash(word[0], word[1]);
		path[1] = ft_strchr(&word[0][idx + 1], '/');
		head = ft_pattern_matchall(&word[0][idx], &word[1][idx], path);
		ft_list_sort(&head, (int (*)(void *, void *))ft_strcmp);
	}
	if (!head)
		ft_lstadd_back(&head, ft_lstnew(word[0]));
	else
		free(word[0]);
	free(path[0]);
	free(word[1]);
	return (head);
}

void	ft_pathname_expansion(t_token *token, t_array *fields)
{
	t_list	*files;
	t_list	*tmp;
	t_list	*field;

	if (!fields || !fields->head)
		return ;
	field = fields->head;
	while (field)
	{
		files = ft_pathname_files(field->content);
		while (files)
		{
			tmp = files->next;
			ft_collector_track(files->content);
			ft_tracked_array_push(&token->fields, files->content);
			free(files);
			files = tmp;
		}
		field = field->next;
	}
}
