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
#include "env.h"
#include "expansion.h"
#include "libft/libft.h"
#include "parser.h"
#include "tokenizer.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int	main(int argc,char ** argv,char ** envp)
{
	t_token	*token;
	t_ast	*node;
	char	*str;

    ft_env_init(envp);
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
		ft_ast_print(node, 0);
		if (!node)
		{
			printf("Parse error.\n");
			free(str);
			continue ;
		}
		while (token)
		{
            if(ft_token_isredirect(token->type) || token->type == TOKEN_WORD)
			expand_token(token);
            token = token->next;
		}
		ft_ast_expansion(node, 0);
		free(str);
		ft_clear();
	}
	clear_history();
	return (0);
	return (0);
}
