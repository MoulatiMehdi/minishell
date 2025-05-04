#include "expand.h"
#include "libft/libft.h"
#include <stddef.h>

extern char	**environ;

int	ft_key_isvalidprefix(char c)
{
    return (c == '_' || ft_isalpha(c));
}

int	ft_key_isvalidsuffix(char c)
{
    return (c == '_' || ft_isalnum(c));
}

char	*ft_env_get(const char *key, size_t len)
{
    int	i;

    if (key == NULL || len <= 0)
        return (NULL);
    i = 0;
    while (environ[i])
    {
        if (ft_strncmp(environ[i], key, len) == 0 && environ[i][len] == '=')
            return (&environ[i][len + 1]);
        i++;
    }
    return (NULL);
}

void ft_word_split(t_array **field,t_word* head)
{
    t_word * p;
    char * str;
    size_t i;

    i = 0;
    p = head;

    str = NULL;
    while(p)
    {
        if(p->type != WORD_NONE)
            ft_strconcat(&str, p->value);
        else 
        {
            while()
        }
        p = p->next;
    }
}

size_t ft_param_namelen(char * str)
{

}

void	ft_param_expand(t_word *p)
{
    char	*str;
    size_t	i;
    size_t	len;

    str = NULL;
    if (p == NULL || p->value == NULL || p->length == 0)
        return ;
    if(p->type == WORD_QUOTE_SINGLE)
    {
        p->value = ft_strndup(p->value, p->length);
        return ;
    }
    i = 0;
    while (i < p->length)
    {
        len = 0;
        if (p->value[i] != '$' || !ft_key_isvalidprefix(p->value[i + 1]))
        {
            while (i + len < p->length && (p->value[i + len] != '$'
                || !ft_key_isvalidprefix(p->value[i + len + 1])))
                len++;
            if (len > 0)
                ft_strnconcat(&str, &p->value[i], len);
        }
        else
        {
            i++;
            len = 1;
            while (i + len < p->length && ft_key_isvalidsuffix(p->value[i
                                                               + len]))
                len++;
            ft_strconcat(&str, ft_env_get(&p->value[i], len));
        }
        i += len;
    }
    p->value = str;
}

void	ft_token_expand(t_token *token)
{
    t_word	*words;
    t_word	*p;

    words = ft_expand_split(token);
    p = words;
    while (p)
    {
        ft_param_expand(p);
        printf("\t - '%s'\n",p->value);
        p = p->next;
    }
    p = words;
    ft_word_split(&token->fields,p);
}
