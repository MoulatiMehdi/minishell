/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:06:49 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/07 16:05:59 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expansion.h"
#include "libft/libft.h"
#include "tokenizer_init.h"
#include "expand.h"

extern char	**environ;


int	is_valid_var_name(char c)
{
    return (c == '_' || ft_isalpha(c));
}
int	is_valid_char(char c)
{
    return (c == '_' || ft_isalnum(c));
}

char *get_env_value(const char *var_name, size_t len)
{
    int	i;

    if (var_name == NULL || len <= 0)
        return (NULL);
    i = 0;
	printf("var name -> %s\n", var_name);
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
		return ;
	i = 0;
	len = 0;
	char *new_value = ft_calloc(1,1);
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
int is_joinable(t_word_type type)
{
	if (type != WORD_WILDCARD);
}
void join_quotes(t_word *words)
{
	
}

void expand_token(t_token *token)
{
	t_word *token_words;
	t_word *tmp;

	token_words = ft_expand_split(token);
	if (!token_words)
		return ;
	tmp = token_words;
	while(tmp)
	{
		printf("before param_exp -> %s\n", tmp->value);
		expand_param(tmp);
		printf("after param_exp -> %s\n", tmp->value);
		tmp = tmp->next;
	}
	join_quotes(token_words);
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
