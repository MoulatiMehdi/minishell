#include "debug.h"
#include "parser.h"
#include "tokenizer.h"

char * ft_asttype_getstr(t_token_type type)
{
    static char *str[20] = {
        "?",
        "W",
        "||",
        "&&",
        "|",
        "(",
        ")",
        "<",
        ">",
        ">>",
        "<<",
        "END",
    };
    return str[type];
}

void ft_ast_tocommand(t_ast * ast)
{
    char * lexeme;
    t_token * token;
    t_list *head;

    if(ast == NULL)
    {
        printf("\033[31m(NULL)\033[0m\n");
        return ;
    }
    head = ast->args;
    while(head)
    {
        token = head->content;
        if(token->value)
            lexeme = strndup(token->value, token->length);
        printf("%s ",lexeme);
        free(lexeme); 
        head = head->next;
    }
    head = ast->redirect;
    while(head)
    {
        token = head->content;
        lexeme = NULL;
        if(token->value)
            lexeme = strndup(token->value, token->length);
        printf("%2s %s",ft_asttype_getstr(token->type),lexeme);
        free(lexeme); 
        head = head->next;
    }
    printf("\n");
}
void ft_list_tokens_print(t_list * head)
{
    char * lexeme;
    t_token * token;
    while(head)
    {
        token = head->content;
        lexeme = strndup(token->value, token->length);
        printf("\t- %s %s\n",ft_token_type(token),lexeme);
        free(lexeme); 
        head = head->next;
    }

}

void ft_ast_print(t_ast * ast)
{
    t_list * p;
    if(ast == NULL)
    {
        printf("NODE NULL\n");
        return ;
    }
    p = ast->args;
    printf ("ARGUMENTS :\n");
    ft_list_tokens_print(p);
    p = ast->redirect;
    printf ("REDIRECTION :\n");
    ft_list_tokens_print(p);
}
