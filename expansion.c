/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:06:49 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/08 13:18:16 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expansion.h"
#include "libft/libft.h"
#include "tokenizer_init.h"
#include "expand.h"

extern char **environ;

int is_valid_var_name(char c)
{
	return (c == '_' || ft_isalpha(c));
}
int is_valid_char(char c)
{
	return (c == '_' || ft_isalnum(c));
}

char *get_env_value(const char *var_name, size_t len)
{
	int i;

	if (var_name == NULL || len <= 0)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var_name, len) == 0 && environ[i][len] == '=')
			return (&environ[i][len + 1]);
		i++;
	}
	return (NULL);
}

void expand_param(t_word *word)
{
	size_t i;
	ssize_t len;

	if (word->type == WORD_QUOTE_SINGLE || word->type == WORD_WILDCARD)
		return;
	i = 0;
	len = 0;
	char *new_value = ft_calloc(1, 1);
	// ! example -> "Hello $USER"
	while (i < word->length)
	{
		len = 0;
		if (word->value[i] == '$' && is_valid_var_name(word->value[i + 1]))
		{
			i++;
			while (i + len < word->length && is_valid_char(word->value[len + i]))
				len++;
			ft_strconcat(&new_value, get_env_value(&word->value[i], len));
		}
		else
		{
			while (i + len < word->length && word->value[i + len] && word->value[i + len] != '$')
				len++;
			ft_strnconcat(&new_value, &word->value[i], len);
		}
		i += len;
	}
	word->value = new_value;
}
// TODO join quotes. | example = this is one token -> "Hel"'lo '$USER | after splitting -> hel lo osm | need to join quotes to look like this hello osm

int is_joinable(t_word *word)
{
	return (word->type != WORD_WILDCARD);
}

void join_quotes(t_word *head)
{
	t_word *curr = head;
	t_word *next;
	char *joined;

	while (curr && curr->next)
	{
		next = curr->next;
		if (is_joinable(curr) && is_joinable(next))
		{
			joined = ft_strjoin(curr->value, next->value);
			if (!joined)
				return;
			curr->value = joined;
			curr->length = ft_strlen(joined);

			curr->next = next->next;
			ft_free((void *)next->value);
			ft_free(next);
		}
		else
			curr = curr->next;
	}
}
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
void field_splitting(t_token *token, t_word *word)
{
	size_t i = 0;
	if (!word || word->length <= 0 || word->type != WORD_NONE)
		return;
	printf("%ld\n",ft_count_word(word->value,IFS));
	
}

void expand_token(t_token *token)
{
	t_word *token_words;
	t_word *tmp;

	token_words = ft_expand_split(token);
	if (!token_words)
		return;
	tmp = token_words;
	while (tmp)
	{
		expand_param(tmp);
		tmp = tmp->next;
	}
	join_quotes(token_words);
	field_splitting(token, token_words);
	while (token_words)
	{
		printf("%s\n", token_words->value);
		token_words = token_words->next;
	}
}

void expand_ast(t_ast *node, int last_status)
{
	t_token *token;
	t_list *list;
	t_list *child;
	if (!node)
		return;
	list = node->args;
	while (list)
	{
		token = list->content;
		if (token && token->type != TOKEN_REDIRECT_HERE)
		{
			expand_token(token);
			// if (should_split(token))
			// 	field_split_token(&list, token);
		}
		list = list->next;
	}
	list = node->redirect;
	while (list)
	{
		token = list->content;
		if (token && token->type != TOKEN_REDIRECT_HERE)
			expand_token(token);
		// if (should_split(token))
		// 	field_split_token(&list, token);
		list = list->next;
	}
	child = node->children;
	while (child)
	{
		expand_ast((t_ast *)child->content, last_status);
		child = child->next;
	}
}