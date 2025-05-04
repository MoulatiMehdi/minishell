#include "expand.h"
#include "libft/libft.h"
#include "tokenizer_init.h"

t_word_type	ft_word_type(char c)
{
	if (c == '"')
		return (WORD_QUOTE_DOUBLE);
	if (c == '\'')
		return (WORD_QUOTE_SINGLE);
	return (WORD_NONE);
}

static size_t	ft_quotelen(const char *str, char c)
{
	size_t	i;

	if (c != '"' && c != '\'')
		return (0);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

t_word	*ft_expand_split(t_token *token)
{
	size_t	i;
	size_t	len;
	t_word	*head;

    if(token == NULL || token->value ==NULL || token ->length == 0)
        return NULL;
    i = 0;
    head = NULL; 
    while(i < token->length)
    {
        if(ft_char_isquote(token->value[i]))
        {
            len = ft_quotelen(&token->value[i + 1], token->value[i]);
            ft_word_push(&head,ft_word_type(token->value[i]), &token->value[i + 1], len);
            i += 2 + len;
        }
        else if(token->value[i] == '*')
        {
            ft_word_push(&head, WORD_WILDCARD, &token->value[i],1);
            while(token->value[i] == '*' && i < token->length)
                i++;
        }
        else 
        {
            len = 0;
            while(token->value[i + len] && !ft_char_isquote(token->value[i + len]) && token->value[i + len] != '*')
                len ++;
            ft_word_push(&head,WORD_NONE, &token->value[i], len);
            i += len;
        }
    }
    return head;
}
