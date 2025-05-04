/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:11:48 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/04 21:10:37 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "expansion.h"
#include "libft/libft.h"
#include "parser.h"
#include "tokenizer.h"
#include <readline/readline.h>
#include <stdio.h>

void	ft_token_expand(t_token *token);

int	main(void)
{
	t_token	*token;
	t_token	*token_cpy;
	t_ast	*node;
	char	*str;

	setvbuf(stdout, NULL, _IONBF, 0);
	while (1)
	{
		str = readline("\033[32mMinishell\033[0m\033[31m>\033[0m ");
		if (str == NULL)
			break ;
		token = tokenize(str);
		if (!token)
		{
			free(str);
			continue ;
		}
		lexer(token);
    
        while(token)
        {
            if(token->type == TOKEN_WORD || (ft_token_isredirect(token->type) && token->value != NULL ))
            {
                printf("\n**************************\n");
                write(1,"\t\t ",3);
                write(1,token->value,token->length);
                write(1," : \n",4);
                ft_token_expand(token);
            }
            token = token ->next;
        }
        free(str);
	}
	return (0);
}
