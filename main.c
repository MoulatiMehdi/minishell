/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:09:35 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/10 18:28:30 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "debug.h"
# include "execution.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
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
    t_ast * node;
    pid_t pid;
    char	*str;
    int wstatus;
    unsigned char exit_code;
    
    while (1)
    {
        ft_putstr_fd(SHELL_PROMPT,2);
        str = readline("");
        if (str == NULL)
            break ;
        token = tokenize(str);
        lexer(token);
        /*printf("LEXER : \n");*/
        /*ft_lexer_print(token);*/
        node = ft_ast_simplecommand(&token);
        ft_execute_simplecommand(node);
        waitpid(-1,&wstatus,0);
        if(WIFEXITED(wstatus))
            exit_code = WEXITSTATUS(wstatus);
        if(WIFSIGNALED(wstatus))
            exit_code = WTERMSIG(wstatus);
        if(WIFSTOPPED(wstatus) )
            exit_code = WSTOPSIG(wstatus);
        if(WIFCONTINUED(wstatus))
        {

            printf("process resumed\n");
        }
        printf("Status : %d\n",exit_code);
        ft_ast_free(node);
        free(str);
    }
    return (0);
}
