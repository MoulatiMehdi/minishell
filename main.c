/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:11:48 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/05 14:24:13 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "debug.h"
#include "parser.h"
#include "tokenizer.h"
#include "expansion.h"
#include <stdio.h>
#include <readline/readline.h>


int main(void)
{
	t_token *token;
	t_token *token_cpy;
	t_ast *node;
	char *str;

	setvbuf(stdout, NULL, _IONBF, 0);
	while (1)
	{
		str = readline("\033[32mMinishell\033[0m\033[31m>\033[0m ");
		if (str == NULL)
			break;

		token = tokenize(str);
		if (!token)
		{
			free(str);
			continue;
		}

		lexer(token);
		// print_token_list(token);
		token_cpy = token;
		node = ft_ast_andor(&token_cpy);

		if (!node)
		{
			printf("Parse error.\n");
			free(str);
			continue;
		}

		expand_ast(node, 0);
		ft_ast_print(node,0);
		ft_ast_free(node);
		free(str);
	}
	return (0);
}
