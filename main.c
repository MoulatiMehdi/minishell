/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:11:48 by okhourss          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "expansion.h"
#include "libft/libft.h"
#include "parser.h"
#include "tokenizer.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int	main(void)
{
	t_token	*token;
	t_ast	*node;
	char	*str;

	setvbuf(stdout, NULL, _IONBF, 0);
	while (1)
	{
		str = readline("\033[32mMinishell\033[0m\033[31m>\033[0m ");
		if (str == NULL)
			break ;
		if (*str)
			add_history(str);
		token = tokenize(str);
		if (!token)
		{
			free(str);
			continue ;
		}
		lexer(token);
		node = parser(token);
		if (!node)
		{
			printf("Parse error.\n");
			free(str);
			continue ;
		}
		while (token)
		{
			expand_token(token);
			token = token->next;
		}
		ft_ast_print(node, 0);
		free(str);
		ft_clear();
	}
	clear_history();
	return (0);
	return (0);
}
