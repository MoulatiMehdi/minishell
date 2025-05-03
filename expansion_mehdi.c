# include "expand.h"
#include "libft/libft.h"

extern char **environ;

int ft_key_isvalidprefix(char c)
{
	return (c == '_' || ft_isalpha(c));
}

int ft_key_isvalidsuffix(char c)
{
	return (c == '_' || ft_isalnum(c));
}

char *ft_env_get(const char *key)
{
	int i;
	int len;

    if(key == NULL)
        return NULL;
	len = ft_strlen(key);
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], key, len) == 0 && environ[i][len] == '=')
			return (&environ[i][len + 1]);
		i++;
	}
	return (NULL);
}

size_t ft_word_expanded_length(t_word * word)
{

}

char * ft_word_expand(t_array ** field,t_word * p)
{
    char  * str;
    size_t i;
    size_t len;

    str = NULL;
    if(p->value == NULL || p->length == 0)
        return NULL;
    i = 0;
    if(p->type == WORD_QUOTE_SINGLE)
        str = ft_strndup(p->value,p->length);
    else if(p->type == WORD_QUOTE_DOUBLE)
    {
        while(i < p->length)
        {
            len = 0;
            while(i + len < p->length && p->value[i] != '$')
                len ++;
            if(len > 0)
                ft_strconcat(&str, ft_strndup(&p->value[i],len));
            i += len;
            if(p->value[i] == '$' && ft_key_isvalidprefix(p->value[i +1]))
            {
                 
            }

        }
    }  
    else 
    {

    }
}

void ft_token_expand(t_token * token)
{
    t_word * words;
    t_word * p;

    words = ft_expand_split(token);
    p = words;
    while(p)
    {
        ft_word_expand(&token->fields, p);
        p = p->next;
    }
}
