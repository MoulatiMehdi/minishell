# include "expansion.h"
# include "libft/libft.h"
#include "word.h"


char * ft_pathname_getcurr(t_word * word)
{
    char *path;
    size_t len;
    size_t idx_wild;
    
    path = ft_word_join(word);
    idx_wild = 0;
    while(word)
    {
        len = 0;
        if(word->type == WORD_NONE)
            while(len < word->length)
            {
                if(word->value[len] == '*')
                {
                    idx_wild += len;
                    if(idx_wild == 0)
                        return NULL;
                    else 
                    {
                        path[idx_wild + 1] = '\0';
                        return path;
                    }
                }
                len ++;
            }
        else 
            idx_wild += word->length;
        word = word->next;
    }
    return NULL;
}


t_list * ft_pathname_getfiles(t_word * words)
{
    char * prefix;

    prefix = ft_pathname_getcurr(words);
    printf("path : %s\n",prefix); 
    return NULL;
}


void pathname_expansion(t_token *token,t_array * fields)
{
    t_list * j;
    t_list * p;
    t_list * list_str;
   
    if(!fields || !fields->head)
        return ;
    p = fields->head;
    while(p)
    {
        list_str = ft_pathname_getfiles(p->content);
        if(list_str)
        {
            j = list_str;
            while(j)
            {
                ft_array_push(&token->fields,j->content);
                j = j->next;
            }
        }
        else 
            ft_array_push(&token->fields, ft_word_join(p->content));
        p = p->next;
    }
    
}
