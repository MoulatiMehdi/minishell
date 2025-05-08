// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   expansion_old.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/04/25 16:31:07 by okhourss          #+#    #+#             */
// /*   Updated: 2025/05/08 11:31:37 by okhourss         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "expansion.h"
// #include <stdlib.h>
// #include <string.h>
// #include <stdio.h>

// extern char **environ;

// int is_var_char(char c)
// {
// 	return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
// }

// char *get_env_value(const char *var_name)
// {
// 	int i;
// 	int len;

// 	len = strlen(var_name);
// 	i = 0;
// 	while (environ[i])
// 	{
// 		if (strncmp(environ[i], var_name, len) == 0 && environ[i][len] == '=')
// 			return (strdup(&environ[i][len + 1]));
// 		i++;
// 	}
// 	return (strdup(""));
// }

// static void handle_quotes(char c, int *inside_single, int *inside_double)
// {
// 	if (c == '\'' && !(*inside_double))
// 		*inside_single = !(*inside_single);
// 	else if (c == '"' && !(*inside_single))
// 		*inside_double = !(*inside_double);
// }

// static char *append_str(const char *original, const char *add)
// {
// 	size_t len_o;
// 	size_t len_a;
// 	char *new_str;

// 	len_o = ft_strlen(original);
// 	len_a = ft_strlen(add);
// 	new_str = malloc(len_o + len_a + 1);
// 	if (!new_str)
// 		return (NULL);
// 	memcpy(new_str, original, len_o);
// 	memcpy(new_str + len_o, add, len_a);
// 	new_str[len_o + len_a] = '\0';
// 	return (new_str);
// }

// static char *itoa_exit_status(int status)
// {
// 	char buffer[12];

// 	snprintf(buffer, sizeof(buffer), "%d", status);
// 	return (strdup(buffer));
// }

// char *expand_variables(const char *value, int last_status)
// {
// 	int(i), (inside_single), (inside_double);
// 	char *result;
// 	char *tmp;
// 	i = ((inside_single = 0), (inside_double = 0), 0);

// 	result = ft_calloc(1, 1);
// 	if (!result)
// 		return (NULL);
// 	while (value[i])
// 	{
// 		handle_quotes(value[i], &inside_single, &inside_double);
// 		if (value[i] == '\'' || value[i] == '"')
// 		{
// 			char buf[2] = {value[i], '\0'};
// 			tmp = append_str(result, buf);
// 			free(result);
// 			result = tmp;
// 			i++;
// 			continue;
// 		}
// 		if (value[i] == '$' && !inside_single)
// 		{
// 			i++;
// 			if (value[i] == '?')
// 			{
// 				char *status_str;

// 				status_str = itoa_exit_status(last_status);
// 				tmp = append_str(result, status_str);
// 				free(status_str);
// 				free(result);
// 				result = tmp;
// 				i++;
// 			}
// 			else if (is_var_char(value[i]))
// 			{
// 				int start = i;
// 				while (is_var_char(value[i]))
// 					i++;
// 				char *var_name = strndup(&value[start], i - start);
// 				char *var_value = get_env_value(var_name);
// 				free(var_name);
// 				tmp = append_str(result, var_value);
// 				free(var_value);
// 				free(result);
// 				result = tmp;
// 			}
// 			else
// 			{
// 				tmp = append_str(result, "$");
// 				free(result);
// 				result = tmp;
// 			}
// 		}
// 		else
// 		{
// 			char buf[2];

// 			buf[0] = value[i];
// 			buf[1] = '\0';
// 			tmp = append_str(result, buf);
// 			free(result);
// 			result = tmp;
// 			i++;
// 		}
// 	}

// 	return (result);
// }

// // TODO need to add strndup to libft

// void expand_token(t_token *token, int last_status)
// {
// 	char *original;
// 	char *expanded;

// 	if (!token || !token->value)
// 		return;
// 	original = strndup(token->value, token->length);
// 	if (!original)
// 		return;
// 	printf("original: %s\n", original);
// 	expanded = expand_variables(original, last_status);
// 	free(original);
// 	if (!expanded)
// 		return;
// 	token->value = expanded;
// 	token->length = strlen(expanded);
// 	printf("expanded: %s\n", expanded);
// }

// int should_split(t_token *token)
// {
// 	if (!token)
// 		return (0);

// 	if (!token->value || token->value[0] == '\0')
// 		return (0);

// 	if (token->value[0] == '"' || token->value[0] == '\'')
// 		return (0);

// 	return (1);
// }

// void field_split_token(t_list **list, t_token *token)
// {
// 	printf("start of splitting\n");

// 	if (!token)
// 		return;
// 	char **words = ft_split(token->value, "\n\t ");
// 	int count = 0;
// 	while (words[count])
// 	{
// 		printf("word[%d] --> %s\n", count, words[count]);
// 		count++;
// 	}
// 	printf("count %d\n", count);
// }

// void expand_ast(t_ast *node, int last_status)
// {
// 	t_token *token;
// 	t_list *list;
// 	t_list *child;
// 	if (!node)
// 		return;
// 	list = node->args;
// 	while (list)
// 	{
// 		token = list->content;
// 		if (token && token->type != TOKEN_REDIRECT_HERE)
// 		{
// 			expand_token(token, last_status);
// 			if (should_split(token))
// 				field_split_token(&list, token);
// 		}
// 		list = list->next;
// 	}
// 	list = node->redirect;
// 	while (list)
// 	{
// 		token = list->content;
// 		if (token && token->type != TOKEN_REDIRECT_HERE)
// 			expand_token(token, last_status);
// 		if (should_split(token))
// 			field_split_token(&list, token);
// 		list = list->next;
// 	}
// 	child = node->children;
// 	while (child)
// 	{
// 		expand_ast((t_ast *)child->content, last_status);
// 		child = child->next;
// 	}
// }
