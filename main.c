/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:09:35 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/04 13:47:46 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "tokenizer.h"
#include <readline/readline.h>
#include <unistd.h>
# include "word.h"


char	*ft_word_gettype(t_word *token)
{
    switch (token->type)
    {
        case WORD_QUOTE_DOUBLE:
            return ("WORD_QUOTE_DOUBLE");
        case WORD_QUOTE_SINGLE:
            return ("WORD_QUOTE_SINGLE");
        case WORD_WILDCARD : 
            return ("WORD_WILDCARD");
        default:
            return "WORD_NONE";
    }
}

int	main(void)
{
    t_token	*token;
    t_word * head;
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
        head = ft_word_split(token);
        printf("join : %s\n",ft_word_join(head));
        while (head)
        {
            lexeme = NULL;
            if(head->value != NULL)
                lexeme = strndup(head->value, head->length);
            printf("%-30s - %s\n",ft_word_gettype(head),lexeme);
            free(lexeme);
            head = head->next;
        }
        free(str);
        ft_clear();
    }
    return (0);
}
