/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:09:35 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/07 22:23:43 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "parser.h"
# include "expansion.h"
# include "execution.h"
#include <sys/wait.h>

t_ast	*ft_ast_simplecommand(t_token **token);

void debug(t_ast * node)
{
        printf("\n*******************************************\n");
        printf("\t ABSTRACT SYNTAX TREE \n");
        printf("\t========================\n");
        ft_ast_print(node,0);
        printf("\n*******************************************\n");
        printf("\t  COMMAND FROM AST \n");
        printf("\t====================\n");
        ft_ast_tocommand(node);
        printf("\n");
}

int	main(void)
{
    t_token	*token;
    t_token * p;
    t_ast * node;
    t_list *p_lst;
    char	*str;
    
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
        node = ft_ast_simplecommand(&token);

        ft_execute_simplecommand(node);
        wait4(-1,NULL,0,NULL);
        ft_ast_free(node);
        free(str);
    }
    return (0);
}
