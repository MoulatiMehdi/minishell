#ifndef WORD_H 
#define WORD_H

# include "libft/libft.h"
# include "tokenizer_init.h"

typedef enum e_word_type
{
    WORD_NONE,
    WORD_QUOTE_DOUBLE,
    WORD_QUOTE_SINGLE,
    WORD_WILDCARD
} t_word_type;


typedef struct s_word
{
    t_word_type type;
    const char * value;
    size_t length;
    struct s_word * next;
} t_word;


t_word* ft_word_new(t_word_type type,const char * value,size_t length);
t_word * ft_word_push(t_word **head,t_word_type type,const char * value,size_t length);
t_word * ft_word_split(t_token * token);
char * ft_word_join(t_word * word);
#endif 


