/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:06:49 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/08 17:18:33 by vboxuser         ###   ########.fr       */
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

int is_joinable(t_word *word)
{
	size_t i;

	if (!word || word->type == WORD_WILDCARD)
		return (0);
	i = 0;
	while (i < word->length)
	{
		if (ft_strchr(IFS, word->value[i]))
			return (0);
		i++;
	}
	return (1);
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
			curr->type = WORD_QUOTE_SINGLE;
			curr->next = next->next;
			ft_free((void *)next->value);
			ft_free(next);
		}
		else
			curr = curr->next;
	}
}

int is_ifs(char c)
{
	return (c == '\n' || c == '\t' || c == ' ');
}
int is_field_splitting_required(t_word *word)
{
	size_t i;

	i = 0;
	if (!word || word->type != WORD_NONE)
		return 0;
	while (i < word->length)
	{
		if(is_ifs(word->value[i]))
			return 1;
		i++;
	}
	return 0;
}

int is_starting_with_ifs(const char *str)
{
	if (!str || !*str)
		return 0;
	return(is_ifs(*str));
}
int is_ending_with_ifs(const char *str, size_t len)
{
	if (len == 0)
		return(0);
	return (is_ifs(str[len - 1]));
}

void field_splitting(t_token *token, t_word *word)
{
	t_array *fields;
	char *curr_field;
	char **split;
	size_t i;
	fields = NULL;
	curr_field = NULL;
	split = NULL;

	while (word)
	{
		if (!is_field_splitting_required(word))
			ft_strnconcat(&curr_field , word->value, word->length);
		else{
			split = ft_split(word->value,IFS);
			int start_with_ifs = is_starting_with_ifs(word->value);
			int end_with_ifs = is_ending_with_ifs(word->value, word->length);
			i = 0;
			if (start_with_ifs && curr_field)
				ft_array_push(&fields, curr_field);
			while (split && split[i])
			{
				if (i == 0 && !start_with_ifs && curr_field)
				{
					ft_strconcat(&curr_field, split[i]);
					ft_array_push(&fields,curr_field);
					curr_field = NULL;
				}
				else
					ft_array_push(&fields, split[i]);
				i++;
			}
			if (end_with_ifs)
				curr_field = NULL;
			if (split)
					free(split);
		}
		word = word->next;
	}
	if (curr_field)
		ft_array_push(&fields,curr_field);
	token->fields = fields;
}

void ft_word_print(t_word * word,char * label)
{
    printf("\n*************************\n%s\n",label);
	while (word)
	{
		printf("- %s\n",word->value);
        word = word->next;
	}

}

void expand_token(t_token *token)
{
	t_word *token_words;
	t_word *tmp;

	token_words = ft_expand_split(token);
	ft_word_print(token_words, "WORDS SPLITTING");
    if (!token_words)
		return;
	tmp = token_words;
	while (tmp)
	{
		expand_param(tmp);
        tmp = tmp->next;
	}
	ft_word_print(token_words, "EXPANSION VARAIBLE");
	join_quotes(token_words);
	ft_word_print(token_words, "QUOTE JOINNIG");
	field_splitting(token, token_words);
    printf("\n*************************\nFIELD SPLITTING\n");
    while (token->fields->head)
	{
		printf("- %s\n", (char *)token->fields->head->content);
		token->fields->head = token->fields->head->next;
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
