# include "libft.h"

t_array* ft_array_new()
{
    t_array * array;

    array = malloc(sizeof(t_array));
    if(array == NULL)
        return NULL;
    array->head = NULL;
    array->length = 0;
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
    (*array)->head
}
