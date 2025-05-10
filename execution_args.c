# include "execution.h"


size_t ft_args_size(t_ast * ast)
{
    size_t len;
    t_token * token;
    t_list *p;

    if(ast == NULL || ast->args == NULL)
        return 0;
    len = 0;
    p = ast->args;
    while(p)
    {
        token = p->content;
        ft_token_expand(token);
        if(token && token->fields)
            len += token->fields->length; 
        p = p->next;
    }
    return len;
}

size_t ft_args_fields(t_token * token,char ** strs)
{
    size_t len;
    t_list * p;
    t_array * field;

    if(token == NULL)
        return 0;
    field = token->fields;
    if(field == NULL || field->length == 0)
        return 0;
    len = 0;
    p = field->head;
    while(p)
    {
        strs[len] = p->content;
        len ++;
        p = p->next;
    }
    return len;
}

char ** ft_ast_getargs(t_ast * ast)
{
    char ** strs;
    t_list * p;
    size_t len;
    size_t i;

    if(ast == NULL)
        return NULL;
    len = ft_args_size(ast);
    if(len == 0)
        return NULL;
    strs = malloc(sizeof(char *) * (len + 1UL));
    p = ast->args;
    i = 0;
    while (p) {
        i += ft_args_fields(p->content,&strs[i]); 
        p = p->next;
    }
    strs[i] = NULL;
    return strs;
}
