# include "execution.h"
# include "expansion.h"
#include "libft.h"
#include "tokenizer.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


size_t ft_ast_argssize(t_ast * ast)
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

size_t ft_token_fields(t_token * token,char ** strs)
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
    len = ft_ast_argssize(ast);
    if(len == 0)
        return NULL;
    strs = malloc(sizeof(char *) * (len + 1UL));
    p = ast->args;
    i = 0;
    while (p) {
        i += ft_token_fields(p->content,&strs[i]); 
        p = p->next;
    }
    strs[i] = NULL;
    return strs;
}

int ft_execute_andor(t_ast * ast)
{
    if(ast == NULL)
        return 0;


    return 0;
}

int ft_redirect_dup(t_token * token)
{
    int fd;
    int fd_dup;
    char * str;

    if(token->type == TOKEN_REDIRECT_HERE)
        return 0;
    fd = -1;
    fd_dup = STDOUT_FILENO;
    str = token->fields->head->content;
    if(token->type == TOKEN_REDIRECT_IN)
    { 
        fd = open(str,O_RDONLY | O_CLOEXEC); 
        fd_dup = STDIN_FILENO;
    }
    if(token->type == TOKEN_REDIRECT_OUT)
        fd = open(str,O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0620); 
    if(token->type == TOKEN_REDIRECT_OUT)
        fd = open(str,O_WRONLY | O_APPEND | O_CREAT | O_CLOEXEC, 0620); 
    
    if(fd >= 0)
        dup2(fd, fd_dup);
    return fd;
}

int ft_ast_redirect(t_list * redirect)
{
    t_token * token;

    while(redirect)
    {
        token = redirect->content;
        ft_token_expand(token);
        if(token->fields == NULL || token->fields->length != 1)
        {
            printf("minishell: %s: ambugious redirection\n",strndup(token->value,token->length));
            return 1;
        }
        if(ft_redirect_dup(token) < 0)
        {
            perror(strndup(token->value,token->length));
            return errno;
        }
        redirect = redirect->next;
    }
    return 0; 
}

int ft_execute_simplecommand(t_ast * ast)
{
    pid_t pid;
    char ** args;
    unsigned char status;

    if(ast == NULL)
        return 0;

    pid = fork();
    if(pid < 0)
    {
        perror("minishell: fork");
        exit(errno);
    }else if(pid == 0)
    {
        status = ft_ast_redirect(ast->redirect);
        if(status)
            exit(status);
        args = ft_ast_getargs(ast); 
        if(args == NULL)
            exit(0);
        execve(args[0], args,NULL);
        perror(args[0]); 
        exit(errno);
    }
    return 0;
}
