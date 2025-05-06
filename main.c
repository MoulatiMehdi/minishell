/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:09:35 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/06 19:39:08 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "parser.h"

char ** ft_ast_getargs(t_ast * ast);

void ft_ast_print_args(t_ast * ast)
{
    t_list * p;
    t_ast * node;
    char ** strs;
    size_t i;
   
    if(ast == NULL)
        return ;
    if(ast->type == AST_SIMPLE_COMMAND)
    {
        strs = ft_ast_getargs(ast);
        printf("\n*************************\n");
        if(strs == NULL)
        {
            printf("NULL\n");
            return ;
        }
        i = 0;
        while(strs[i])
        {
            printf("%s\n",strs[i]);
            i++;
        }
    }
    p = ast->children;
    while(p)
    {
        node = p->content;
        ft_ast_print_args(node);
        p = p->next;
    }
}
int	main(void)
{
    t_token	*token;
    t_ast * node;
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
        node = parser(token);
        // printf("\n*******************************************\n");
        // printf("\t ABSTRACT SYNTAX TREE \n");
        // printf("\t========================\n");
        // ft_ast_print(node,0);
        // printf("\n*******************************************\n");
        // printf("\t  COMMAND FROM AST \n");
        // printf("\t====================\n");
        // ft_ast_tocommand(node);
   
        ft_ast_print_args(node);
        printf("\n");
        ft_ast_free(node);
        free(str);
    }
    return (0);
}
