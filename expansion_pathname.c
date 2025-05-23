#include "execution.h"
# include "expansion.h"
# include "libft/libft.h"
#include "word.h"
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char* ft_pattern_prefix(char * word,char * mask)
{
    size_t len;
    size_t slash;
    
    len = 0;
    slash = -1;

    if(word == NULL)
        return NULL;
    while(word[len])
    {
        if(word[len] == '/')
            slash = len;
        if(word[len] == '*' && mask[len] == '1')
            return ft_strndup(word,slash);
        len ++;
    }
    return NULL;
}

char * ft_word_mask(t_word * word)
{
    char * mask;
    size_t i;
    size_t total;

    mask = ft_word_join(word);
    total = 0;
    while(word)
    {
        i = 0;
        while(i < word->length)
        {
            mask[total] = '0';
            mask[total] += word->type == WORD_NONE && word->value[i] == '*';
            i++;
            total ++;
        }
        word = word->next;
    }
    return mask;
}

int ft_path_iscurrentdir(char * prefix)
{
    struct stat curr;
    struct stat path;

    if(!prefix)
        return 0;
    if(stat(".",&curr) != 0 || stat(prefix,&path) != 0)
        return 0;
    
    return (curr.st_ino == path.st_ino && path.st_dev == curr.st_dev);
}

int ft_pattern_isvalid(char * word,char * mask,char * prefix)
{
    int is_slash;
    int wild;
    size_t i;

    is_slash = 0;
    wild = 0;
    i = 0;
    while(word[i])
    {
        if(wild && is_slash)
            return 0;
        if(mask[i] == '1')
            wild ++;
        if(wild && word[i] == '/')
        {
            is_slash = 1 ; 
            while(word[i] == '/')
                i++;
            continue;
        }
        i++;
    }
    return wild != 0 && ft_path_iscurrentdir(prefix);
}


t_list * ft_pattern_getfiles(char * word,char * mask, char  * prefix)
{
    t_list * head;
    size_t idx;
    size_t slash_idx;

    idx = 0;
    head = NULL;
    while(word[idx] && mask[idx] == '0')
    {
        if(word[idx] == '/')
            slash_idx = idx;
        idx ++;
    }
    while(word[slash_idx])
    {
        opendir();

    }
    return NULL;
}

void pathname_expansion(t_token *token,t_array * fields)
{
    t_list * j;
    t_list * p;
    char * mask;
    char * word;
    char * prefix;
    
    if(!fields || !fields->head)
        return ;
    p = fields->head;
    while(p)
    {
        word = ft_word_join(p->content);
        mask = ft_word_mask(p->content);
        prefix = ft_pattern_prefix(word, mask);
        if(ft_pattern_isvalid(word,mask,prefix))
        {
            j = ft_pattern_getfiles(prefix,word,mask);
            while(j)
            {
                ft_array_push(&token->fields,j->content);
                j = j->next;
            }
        }
        else
            ft_array_push(&token->fields,word);
        free(mask);
        p = p->next;
    }
}
