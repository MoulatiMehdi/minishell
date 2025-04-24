#include "debug.h"

void ft_lexer_print(t_token * token)
{
    char	*lexeme;

    while (token)
    {
        lexeme = strndup(token->value, token->length);
        printf("%-30s : %s\n", ft_token_type(token), lexeme);
        free(lexeme);
        token = token->next;
    }
}
