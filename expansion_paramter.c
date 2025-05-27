/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_paramter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:00:52 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/27 08:47:33 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft/libft.h"

int	is_valid_var_name(char c)
{
	return (c == '_' || ft_isalpha(c) || c == '?');
}

int	is_valid_char(char c)
{
	return (c == '_' || ft_isalnum(c));
}

size_t	ft_expand_param(t_word *word, size_t i, char **val)
{
	size_t	len;

	len = word->value[i] == '?';
	if (len == 0)
	{
		while (i + len < word->length && is_valid_char(word->value[len + i]))
			len++;
	}
	ft_strconcat(val, ft_env_getvaluebysubstr((char *)&word->value[i], len));
	return (len);
}

size_t	ft_expand_noparam(t_word *word, size_t i, char **val)
{
	size_t	len;

	len = 1;
	while (i + len < word->length)
	{
		if (!word->value[i + len] || word->value[i + len] == '$')
			break ;
		len++;
	}
	ft_strnconcat(val, &word->value[i], len);
	return (len);
}

void	expand_param(t_word *word)
{
	size_t	i;
	ssize_t	len;
	char	*new_value;

	if (word->type == WORD_QUOTE_SINGLE)
	{
		word->value = ft_strndup_track(word->value, word->length);
		return ;
	}
	i = 0;
	new_value = ft_calloc(1, 1);
	while (i < word->length)
	{
		if (word->value[i] == '$' && is_valid_var_name(word->value[i + 1]))
		{
			i++;
			len = ft_expand_param(word, i, &new_value);
		}
		else
			len = ft_expand_noparam(word, i, &new_value);
		i += len;
	}
	ft_collector_track(new_value);
	word->value = new_value;
	word->length = ft_strlen(new_value);
}
