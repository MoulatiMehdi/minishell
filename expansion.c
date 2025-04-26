/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:31:07 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/25 16:31:07 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern char **environ;

int is_var_char(char c)
{
	return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

char *get_env_value(const char *var_name)
{
	int i;
	int len;

	len = strlen(var_name);
	i = 0;
	while (environ[i])
	{
		if (strncmp(environ[i], var_name, len) == 0 && environ[i][len] == '=')
			return (&environ[i][len + 1]);
		i++;
	}
	return (NULL);
}

void handle_quotes(const char *value, int *i, int *inside_single, int *inside_double)
{
	if (value[*i] == '\'' && !(*inside_double))
	{
		*inside_single = !(*inside_single);
		(*i)++;
	}
	else if (value[*i] == '"' && !(*inside_single))
	{
		*inside_double = !(*inside_double);
		(*i)++;
	}
}

char *expand_variables(const char *value, int last_status)
{
	(void)value;
	(void)last_status;
	return (NULL);
}

void expand_token(t_token *token, int last_status)
{
	char *original;
	char *expanded;

	if (!token || !token->value)
		return;
	original = strndup(token->value, token->length);
	if (!original)
		return;
	printf("original: %s\n", original);
	return;
	expanded = expand_variables(original, last_status);
	free(original);
	if (!expanded)
		return;
	token->value = expanded;
	token->length = strlen(expanded);
}

void expand_ast(t_ast *node, int last_status)
{
	t_token *token;
	t_list *list;

	if (!node)
		return;
	list = node->args;
	printf("list -> %p\n", list);
	printf("node -> %p\n", node);
	printf("node->args -> %p\n", node->args);
	while (list)
	{
		token = list->content;
		if (token && token->type == TOKEN_WORD)
			expand_token(token, last_status);
		list = list->next;
	}
	list = node->redirect;
	while (list)
	{
		token = list->content;
		if (token && token->type == TOKEN_WORD)
			expand_token(token, last_status);
		list = list->next;
	}
}
