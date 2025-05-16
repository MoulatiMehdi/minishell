#include "expand.h"
#include "libft/libft.h"
#include "tokenizer.h"
#include <stddef.h>


#define IFS " \t\n"

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


int ft_quotes_isjoinable(t_word * word)
{
    size_t i;
    if(word == NULL || word->type == WORD_WILDCARD)
        return 0;
    if(word->type !=  WORD_NONE)
        return word->type != WORD_NONE;
    if(word->value == NULL)
        return 1;
    i = 0;
    while(word->value[i])
    {
        if(ft_strchr(IFS, word->value[i]) != NULL)
            return  0;
        i++;
    }
    return 1;
}
void ft_field_split(t_array ** field,t_word * words)
{
    t_word * word;
    char * str;
    char ** strs;
    size_t len;
    size_t i;

    str = NULL;
    word = words;
    while(word)
    {
        if(word->type == WORD_QUOTE_SINGLE || word->type == WORD_QUOTE_DOUBLE )
            ft_strconcat(&str, word->value);
        else if (word->type == WORD_NONE)
        {
            if(str != NULL && ft_strchr(IFS, word->value[0]))
            {
                ft_array_push(field, str);
                str = NULL;
            }
            strs = ft_split(word->value, IFS);
            if(strs)
            {
                ft_strconcat(&str,strs[0]);
                free(strs[0]);
                strs[0] = str;
                len = ft_strlen(word->value);
                if(ft_strchr(IFS,word->value[len - 1]) == NULL)
                {
                    len = 0;
                    while(strs[len])
                        len ++;
                    str = strs[len - 1];
                    strs[len - 1] = NULL;
                }
                else  
                    str = NULL; 
                i = 0;
                while (strs[i]) {
                    ft_array_push(field, strs[i]);
                    i++;
                }
            }
        }else 
        {

        }
        word = word->next;
    }
    if(str)
        ft_array_push(field, str);
}

void ft_quotes_join(t_word* head)
{
    t_word * p;
    t_word * p_next;

    p = head;
    while(p)
    {
        if(ft_quotes_isjoinable(p))
        {
            p->type = WORD_QUOTE_SINGLE;
            p_next = p->next;
            while(p_next && ft_quotes_isjoinable(p_next))
            {
                ft_strconcat((char **)&p->value, p_next->value);
                p->next = p_next->next;
                free((char *)p_next->value);
                free(p_next);
                p_next = p->next;
            }
            if(p_next != NULL)
                p = p_next;
        }
        p = p->next;
    }
}

void	ft_param_expand(t_word *p)
{
    char	*str;
    size_t	i;
    size_t	len;

    str = NULL;
    if (p == NULL || p->value == NULL)
        return ;
    if(p->length == 0 || p->type == WORD_QUOTE_SINGLE || p->type == WORD_WILDCARD)
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

    if(token->type == TOKEN_REDIRECT_HERE)
        return ;
    words = ft_expand_split(token);
    p = words;
    while (p)
    {
        ft_param_expand(p);
        p = p->next;
    }
    ft_quotes_join(words);
    p = words;
    ft_field_split(&token->fields,words);
}
