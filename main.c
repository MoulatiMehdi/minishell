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

char * ft_asttype_getstr(t_token_type type);
t_ast	*ft_ast_andor(t_token **token);

int	main(void)
{
    t_token	*token;
    t_token	*token_cpy;
    t_ast * node;
    char	*str;
    char * lexeme;
    
    setvbuf(stdout, NULL, _IONBF, 0);
    while (1)
    {
        str = readline(" \033[32mMinishell\033[0m\033[31m>\033[0m ");
        if (str == NULL)
            break ;
        token = tokenize(str);
        lexer(token);
        /*printf("LEXER : \n");*/
        /*ft_lexer_print(token);*/
        token_cpy = token;
        node = ft_ast_andor(&token_cpy);
        printf("\n*******************************************\n");
        printf("\t ABSTRACT SYNTAX TREE \n");
        printf("\t========================\n");
        ft_ast_print(node,0);
        printf("\n*******************************************\n");
        printf("\t  COMMAND FROM AST \n");
        printf("\t====================\n");
        ft_ast_tocommand(node);
        printf("\n");
        if(token_cpy != NULL && token_cpy->type != TOKEN_EOI)
        {
            lexeme = NULL;
            fprintf(stderr,"syntax error near unexpected token ");
            if(token_cpy->type == TOKEN_WORD)
            {
                if(token_cpy->value != NULL)
                    lexeme = strndup(token_cpy->value,token->length);
                fprintf(stderr,"%s\n",lexeme);
            }
            else
                fprintf(stderr,"`%s`\n",ft_asttype_getstr(token_cpy->type));
            free(lexeme);
        }
        ft_ast_free(node);
        free(str);
    }
    return (0);
}
