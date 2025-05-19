#include "debug.h"

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
