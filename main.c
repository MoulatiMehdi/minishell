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

#include "debug.h"
#include "parser.h"
#include <stdio.h>

t_ast	*ft_ast_pipeline(t_token **token);

int	main(void)
{
    t_token	*token;
    t_token	*token_cpy;
    t_ast * node;
    char	*str;

    while (1)
    {
        str = readline(" \033[32mMinishell\033[0m\033[31m>\033[0m ");
        if (str == NULL)
            break ;
        token = tokenize(str);
        lexer(token);
        printf("LEXER : \n");
        ft_lexer_print(token);
        token_cpy = token;
        node = ft_ast_pipeline(&token_cpy);
        printf("--------------------\n");
        printf("AST : \n");
        ft_ast_print(node);
        printf("--------------------\n");
        printf("AST -> COMMAND : \n");
        ft_ast_tocommand(node);
        ft_ast_free(node);
        free(str);
    }
    return (0);
}
