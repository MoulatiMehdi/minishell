#include "debug.h"
#include "parser.h"
#include "tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STR_EMPTY   "        "
#define STR_TBR "┣━━━━━━ "
#define STR_TB  "┃       "
#define STR_TR  "┗━━━━━━ "

char* g_indent[1024];

char * ft_ast_gettype(t_ast * ast)
{
    if(ast == NULL) 
        return "NULL";
    switch (ast->type) {
        case AST_PIPELINE : 
            return "\033[1;32mAST_PIPELINE\033[0m";
        case AST_COMMAND : 
            return "AST_COMMAND";
        case AST_SIMPLE_COMMAND: 
            return "\033[1;33mAST_SIMPLE_COMMAND\033[0m";
        case AST_AND_OR: 
            return "\033[1;34mAST_AND_OR";
        case AST_SUBSHELL: 
            return "\033[1;34mAST_SUBSHELL\033[0m";
        case AST_OR: 
            return "\033[1;35mAST_OR\033[0m";
        case AST_AND: 
            return "\033[1;35mAST_AND\033[0m";
        case AST_PIPE : 
            return "\033[1;35mAST_PIPE\033[0m";
        default: 
            return "AST_UNKNOWN";
    }
}



void leaf_print(t_list *p ,int depth)
{
    int i;

    i = 0;
    if(p != NULL && p->next != NULL)
        g_indent[depth] = STR_TB;
    else
        g_indent[depth] = STR_EMPTY;
    while(i < depth)
    {
        printf("%s",g_indent[i]);
        i++;
    }
    if(p->next != NULL)
        printf(STR_TBR);
    else 
        printf(STR_TR);
}

char * ft_asttype_getstr(t_token_type type)
{
    static char *str[20] = {
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
        "newline",
    };
    return str[type];
}


void ft_char_repete(char* str,int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        printf("%s",str);
        i++;
    }
}


void ft_ast_args_print(t_ast * ast,int depth)
{
    t_list * head;
    t_list * field;
    t_token * token;

    if(ast == NULL)
        return ;
    head = ast->args;
    while(head)
    {
        token = head->content;
        if(token->fields)
        {
            field = token->fields->head;
            while(field)
            {
                leaf_print(field,depth);
                printf("%s\n",(char *)field->content);
                field = field->next;
            }
        }
        head = head->next;
    }
}


void ft_ast_redirect_print(t_ast * ast,int depth)
{
    t_list * head;
    t_token * token;
    char * lexeme;

    if(ast == NULL)
        return ;
    head = ast->redirect;
    while(head)
    {
        token = head->content;
        lexeme = NULL;
        if(token->value)
            lexeme = strndup(token->value, token->length);
        else 
            lexeme = NULL;
        leaf_print(head,depth);
        printf("%s %s \n",ft_asttype_getstr(token->type),lexeme);
        free(lexeme); 
        head = head->next;
    }
}


void ft_ast_children_print(t_ast * ast)
{
    t_list * head;

    if(ast == NULL)
        return ;
    if (ast->type == AST_AND)
        write(1,"&& ",3);
    if (ast->type == AST_OR)
        write(1,"|| ",3);
    head = ast->children;
    if(head)
    {
        if(ast->type == AST_SUBSHELL)
            write(1,"( ",2);
        ft_ast_tocommand(head->content);
        head = head->next;
    }
    while(head)
    {
        if(ast->type == AST_PIPELINE)
            write(1,"| ",2);
        ft_ast_tocommand(head->content);
        head = head->next;
    }
    if(ast->type == AST_SUBSHELL)
        write(1,") ",2);
}

void ft_ast_tocommand(t_ast * ast)
{
    if(ast == NULL)
    {
        printf("\033[31m(NULL)\033[0m\n");
        return ;
    }
    ft_ast_args_print(ast,0);
    if(ast->type != AST_SUBSHELL)
        ft_ast_redirect_print(ast,0);
    ft_ast_children_print(ast);
    if(ast->type == AST_SUBSHELL)
        ft_ast_redirect_print(ast,0);
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

void ft_ast_print(t_ast * ast,int depth)
{
    t_list * p;
    t_ast * node;
    if(ast == NULL)
        return ;
    printf("%s : \n",ft_ast_gettype(ast));
    ft_ast_args_print(ast,depth);
    ft_ast_redirect_print(ast,depth);
    p = ast->children;
    while(p)
    {
        node = p->content;
        leaf_print(p,depth);
        ft_ast_print(node,depth +1);
        p = p->next;
    }
}
