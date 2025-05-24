/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_pathname.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:00:55 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/24 10:25:45 by mmoulati         ###   ########.fr       */
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

char	*ft_pattern_prefix(char *word, char *mask)
{
	size_t	len;
	size_t	slash;
	int		found;

	len = 0;
	slash = 0;
	found = 0;
	if (word == NULL)
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

int	ft_pattern_isvalid(char *word, char *mask, char *prefix)
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

size_t	ft_pattern_lastslash(char *word, char *mask)
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

int	ft_namecmp(void *name1, void *name2)
{
	size_t	i;
	char	*str1;
	char	*str2;
	int		test;

	str1 = name1;
	str2 = name2;
	if (name1 == NULL || name2 == NULL)
		return (name1 - name2);
	i = 0;
	while (1)
	{
		test = ft_tolower(str1[i]) - ft_tolower(str2[i]);
		if (test != 0 || !str2[i])
			return (test);
		i++;
	}
	i = 0;
	while (1)
	{
		if (str2[i] - str1[i] != 0 || !str2[i])
			return (str2[i] - str1[i]);
		i++;
	}
	return (0);
}

t_list	*ft_pattern_files(char *word, char *mask)
{
	size_t	idx;
	t_list	*head;
	t_list	*p;
	char	*is_path;
	char	*prefix;

	head = NULL;
	prefix = ft_pattern_prefix(word, mask);
	if (!word || !ft_pattern_isvalid(word, mask, prefix))
		return (NULL);
	idx = ft_pattern_lastslash(word, mask);
	is_path = ft_strchr(&word[idx + 1], '/');
	head = ft_pattern_matchall(&word[idx], &mask[idx], prefix, is_path);
	ft_list_sort(&head, ft_namecmp);
	if (is_path)
	{
		p = head;
		while (p)
		{
			ft_strconcat((char **)&p->content, "/");
			p = p->next;
		}
	}
	free(prefix);
	return (head);
}

void	pathname_expansion(t_token *token, t_array *fields)
{
	t_list	*files;
	t_list	*tmp;
	t_list	*field;
	char	*mask;
	char	*word;

	if (!fields || !fields->head)
		return ;
	field = fields->head;
	while (field)
	{
		word = ft_word_join(field->content);
		mask = ft_word_mask(field->content);
		files = ft_pattern_files(word, mask);
		free(mask);
		if (files == NULL)
			ft_array_push(&token->fields, word);
		else
		{
			while (files)
			{
				tmp = files->next;
				ft_array_push(&token->fields, files->content);
				free(files);
				files = tmp;
			}
		}
		field = field->next;
	}
}
