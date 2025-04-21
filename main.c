/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:09:35 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/21 18:32:20 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "tokenizer.h"
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

int	main(int argc, char *argv[])
{
	t_token	*token;
	int		len;
	char	str[1024];

	bzero(str, 1024);
	len = read(0, str, 1024);
	str[len - 1] = '\0';
	token = tokenize(str);
	lexer(token);
	while (token)
	{
		printf("%20s : %s\n", ft_token_type(token), strndup(token->value,
				token->length));
		token = token->next;
	}
	return (0);
}
