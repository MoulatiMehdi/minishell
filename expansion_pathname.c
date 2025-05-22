# include "expansion.h"
#include "libft/libft.h"

t_list *ft_pathname_getfiles()
{

}


void pathname_expansion(t_token *token,t_array * fields)
{
    t_list * p;
    t_list * list_str;
   
    if(!fields || !fields->head)
        return ;
    p = fields->head;
    while(p)
    {

        p = p->next;
    }
    
}
