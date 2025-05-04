/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:11:48 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/03 23:15:51 by vboxuser         ###   ########.fr       */
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
		// print_token_list(token);
        
        while(token)
        {
            if(token->type == TOKEN_WORD || ft_token_isredirect(token->type))
            {
                ft_token_expand(token);
                write(1,"\n",1);
            }
            token = token ->next;
        }
        free(str);
	}
	return (0);
}
