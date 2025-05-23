#include "execution.h"
#include "expansion.h"
#include "libft/libft.h"
#include "word.h"
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		ft_pattern_ismatch(char *pattern, char *path, char *mask);
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

char	*ft_word_mask(t_word *word)
{
	char	*mask;
	size_t	i;
	size_t	total;

	mask = ft_word_join(word);
	total = 0;
	while (word)
	{
		i = 0;
		while (i < word->length)
		{
			mask[total] = '0';
			mask[total] += word->type == WORD_NONE && word->value[i] == '*';
			i++;
			total++;
		}
		word = word->next;
	}
	return (mask);
}

int	ft_path_iscurrentdir(char *prefix)
{
	struct stat	curr;
	struct stat	path;

	if (!prefix)
		return (1);
	if (stat(".", &curr) != 0 || stat(prefix, &path) != 0)
		return (0);
	return (curr.st_ino == path.st_ino && path.st_dev == curr.st_dev);
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

char	*ft_diren_getname(DIR *stream)
{
	struct dirent	*dir;

	dir = readdir(stream);
	if (dir == NULL)
		return (NULL);
	return (dir->d_name);
}

DIR	*ft_diren_open(char *path)
{
	if (path)
		return (opendir(path));
	else
		return (opendir("."));
}

t_list	*ft_pattern_matchall(char *word, char *mask, char *prefix,
		char *is_path)
{
	t_list	*head;
	DIR		*stream_dir;
	char	*name;

	head = NULL;
	stream_dir = ft_diren_open(prefix);
	if (is_path)
		is_path[0] = '\0';
	while (1)
	{
		name = ft_diren_getname(stream_dir);
		if (!name)
			break ;
		if (is_path && !ft_path_isdir(name))
			continue ;
		if (ft_pattern_ismatch(word, name, mask))
			ft_lstadd_back(&head, ft_lstnew(ft_strjoin(prefix, name)));
	}
	closedir(stream_dir);
	if (is_path)
		is_path[0] = '/';
	return (head);
}

t_list	*ft_pattern_files(char *word, char *mask)
{
	size_t	slash_idx;
	t_list	*head;
	t_list	*p;
	char	*is_path;
	char	*prefix;

	head = NULL;
	prefix = ft_pattern_prefix(word, mask);
	if (!word || !ft_pattern_isvalid(word, mask, prefix))
		return (NULL);
	slash_idx = ft_pattern_lastslash(word, mask);
	is_path = ft_strchr(word, '/');
	head = ft_pattern_matchall(&word[slash_idx], &mask[slash_idx], prefix,
			is_path);
	if (is_path)
	{
		p = head;
		while (p)
		{
			ft_strconcat((char **)&p->content, "/");
			p = p->next;
		}
	}
	return head;
}

void	pathname_expansion(t_token *token, t_array *fields)
{
	t_list	*files;
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
		if (files == NULL)
			ft_array_push(&token->fields, word);
		else
		{
			while (files)
			{
				ft_array_push(&token->fields, files->content);
				files = files->next;
			}
		}
		field = field->next;
	}
}
