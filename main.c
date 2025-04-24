/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:09:35 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/22 11:20:45 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collector.h"
#include "lexer.h"
#include "tokenizer.h"
#include <readline/readline.h>
#include <unistd.h>

char	*ft_token_type(t_token *token)
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

int	main(void)
{
    t_token	*token;
    char	*str;
    char	*lexeme;

    while (1)
    {
        token = NULL;
        str = readline(" \033[32mMinishell\033[0m\033[31m>\033[0m ");
        if (str == NULL)
            break ;
        token = tokenize(str);
        lexer(token);
        while (token)
        {
            lexeme = NULL;
            if(token->value != NULL)
                lexeme = strndup(token->value, token->length);
            printf("%-30s : %s\n", ft_token_type(token), lexeme);
            free(lexeme);
            token = token->next;
        }
        free(str);
        ft_clear();
    }
    return (0);
}
