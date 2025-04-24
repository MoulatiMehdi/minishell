# include "libft.h"

t_array* ft_array_new()
{
    t_array * array;

    array = malloc(sizeof(t_array));
    if(array == NULL)
        return NULL;
    array->head = NULL;
    array->last = NULL;
    array->length = 0;
    return array;
}

void *ft_array_push(t_array ** array,void * content)
{
    t_list * node;
    if(array == NULL)
        return NULL;
    node = ft_lstnew(content);
    if(node == NULL)
        return NULL;
    if(*array == NULL)
        *array = ft_array_new();
    if((*array)->head == NULL)
        (*array)->head = node;
    if((*array)->last != NULL)
        (*array)->last->next = node;
    (*array)->last = node;
    (*array)->length ++;
    return content;
}

