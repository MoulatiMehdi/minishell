/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:11:48 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/26 14:11:48 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenizer.h"
#include "expansion.h"
#include <stdio.h>
#include <readline/readline.h>

char *ft_token_type(t_token *token)
{
	switch (token->type)
	{
	case TOKEN_EOI:
		return ("TOKEN_EOI");
	case TOKEN_WORD:
		return ("TOKEN_WORD");
	case TOKEN_PIPE:
		return ("TOKEN_PIPE");
	case TOKEN_AND:
		return ("TOKEN_AND");
	case TOKEN_OR:
		return ("TOKEN_OR");
	case TOKEN_REDIRECT_APPEND:
		return ("TOKEN_REDIRECT_APPEND");
	case TOKEN_REDIRECT_IN:
		return ("TOKEN_REDIRECT_IN");
	case TOKEN_REDIRECT_OUT:
		return ("TOKEN_REDIRECT_OUT");
	case TOKEN_REDIRECT_HERE:
		return ("TOKEN_REDIRECT_HERE");
	case TOKEN_PARENS_OPEN:
		return ("TOKEN_PARENS_OPEN");
	case TOKEN_PARENS_CLOSE:
		return ("TOKEN_PARENS_CLOSE");
	default:
		return ("TOKEN_UNKNOWN");
	}
}

void print_token_list(t_token *token)
{
	char *lexeme;

	while (token)
	{
		lexeme = NULL;
		if (token->value != NULL)
			lexeme = strndup(token->value, token->length);
		printf("%-30s : %s\n", ft_token_type(token), lexeme);
		free(lexeme);
		token = token->next;
	}
}

char *ft_ast_gettype(t_ast *ast)
{
	if (ast == NULL)
		return "NULL";
	switch (ast->type)
	{
	case AST_PIPELINE:
		return "\033[1;32mAST_PIPELINE\033[0m";
	case AST_COMMAND:
		return "AST_COMMAND";
	case AST_SIMPLE_COMMAND:
		return "\033[1;33mAST_SIMPLE_COMMAND\033[0m";
	case AST_AND_OR:
		return "\033[1;34mAST_AND_OR";
	case AST_SUBSHELL:
		return "\033[1;34mAST_SUBSHELL\033[0m";
	case AST_OR:
		return "\033[1;35mAST_OR\033[0m";
	case AST_AND:
		return "\033[1;35mAST_AND\033[0m";
	case AST_PIPE:
		return "\033[1;35mAST_PIPE\033[0m";
	default:
		return "AST_UNKNOWN";
	}
}

void print_ast(t_ast *node)
{
	t_list *child;

	if (!node)
	{
		printf("[NULL AST node]\n");
		return;
	}

	printf("=== AST NODE ===\n");
	printf("Node Type: %s\n", ft_ast_gettype(node));

	printf("-- Args --\n");
	print_token_list(node->args);

	printf("-- Redirects --\n");
	print_token_list(node->redirect);

	printf("-- Children --\n");
	child = node->children;
	while (child)
	{
		print_ast((t_ast *)child->content);
		child = child->next;
	}
}

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
		// print_ast(node);
		ft_ast_free(node);
		free(str);
	}
	return (0);
}
