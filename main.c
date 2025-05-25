/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:09:35 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/25 11:23:43 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "libft/libft.h"
#include "parser.h"

char	*ft_asttype_getstr(t_token_type type);
t_ast	*ft_ast_andor(t_token **token);

int	main(void)
{
	t_token	*token;
	t_ast	*node;
	char	*str;

	ft_signal_parent();
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
		printf("\n*******************************************\n");
		printf("\t ABSTRACT SYNTAX TREE \n");
		printf("\t========================\n");
		ft_ast_print(node, 0);
		printf("\n*******************************************\n");
		printf("\t  COMMAND FROM AST \n");
		printf("\t====================\n");
		ft_ast_tocommand(node);
		printf("\n");
		free(str);
		ft_clear();
	}
	return (0);
}
