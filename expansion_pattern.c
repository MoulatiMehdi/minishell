# include "execution.h"
#include "libft/libft.h"
#include <stddef.h>

char * ft_strnmatch(char * src,char * to_find,size_t n)
{
    size_t i;
// TODO: protect this function from segv
    i = 0;
    while(src[i])
    {
        if(ft_strncmp(&src[i], to_find, n) == 0)
            return &src[i];
        i++;
    }
    return NULL;
}

int ft_pattern_ismatch(char * pattern,char * path,char * mask)
{
    size_t i;
    size_t j;
    size_t len;
    char * ptr;

    i = 0;
    j = 0;

    if(mask[0] == '1' && path[0] == '.')
        return 0;
    while(pattern[i])
    {
        if(mask[i] == '1')
        {
            len = 0;
            while(mask[i] == '1')
                i++;
            if(!pattern[i])
                return 1;
            while(mask[i + len] == '0')
                len ++;
            ptr = &pattern[i];
            while(1)
            {
                ptr = ft_strnmatch(&path[j],ptr,len);
                if(!ptr)
                    return 0;
                if(ft_pattern_ismatch(&pattern[i + len],&ptr[len],&mask[i + len]))
                        return 1;
                j+= len;
            }
            i += len;
        }
        else if (pattern[i] != path[j])
            return 0;
        else 
        {
            i++;
            j++;
        }
    }
    return 1;
}

