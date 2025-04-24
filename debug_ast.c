#include "debug.h"

void ft_ast_tocommand(t_ast * ast)
{
    char * lexeme;
    t_token * token;
    t_list *head;

    head = ast->args;
    while(head)
    {
        token = head->content;
        lexeme = strndup(token->value, token->length);
        printf("%s ",lexeme);
        free(lexeme); 
        head = head->next;
    }
    head = ast->redirect;
    while(head)
    {
        token = head->content;
        lexeme = strndup(token->value, token->length);
        printf("< %s ",lexeme);
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
        printf("\t- %s\n",lexeme);
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
