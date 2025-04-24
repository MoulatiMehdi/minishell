/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:58:24 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/23 17:58:24 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenizer.h"
# include "libft/libft.h"


t_ast	*ft_ast_andor(t_token **token);

t_ast_type	ft_ast_fromtoken(t_token_type type)
{
    if (type == TOKEN_OR)
        return (AST_OR);
    if (type == TOKEN_AND)
        return (AST_AND);
    if (type == TOKEN_PIPE)
        return (AST_PIPE);
    return AST_UNKNOWN;
}

t_ast	*ft_ast_simplecommand(t_token **token)
{
    t_token_type	token_type;
    t_ast			*node;

    if (*token == NULL)
        return (NULL);
    node = ft_ast_new(AST_SIMPLE_COMMAND); 
    while(1)
    {
        token_type = (*token)->type;
        if(token_type == TOKEN_WORD)
            ft_lstadd_back(&node->args,ft_lstnew(*token));
        else if(ft_token_isredirect(token_type))
        {
            if((*token)->value == NULL)
                return ft_ast_free(node);
            ft_lstadd_back(&node->redirect,ft_lstnew(*token));
        }
        else 
            break;
        *token = (*token)->next;
    }
    if(node->redirect == NULL && node->args == NULL)
        return ft_ast_free(node);
    return node;
}

t_ast	*ft_ast_subshell(t_token **token)
{
    t_ast * parent_node;
    t_ast * child_node;
    if(!*token || (*token)->type != TOKEN_PARENS_OPEN)
        return NULL;
    *token = (*token)->next; 
    child_node = ft_ast_andor(token); 
    if(!child_node || (*token)->type != TOKEN_PARENS_CLOSE)
        return ft_ast_free(child_node);
    *token = (*token)->next; 
    parent_node = ft_ast_new(AST_SUBSHELL);
    ft_lstadd_back(&parent_node->children,ft_lstnew(child_node));
    return parent_node;
}

t_ast	*ft_ast_command(t_token **token)
{
    t_ast			*node;
    t_token_type token_type;
    if (*token == NULL)
        return (NULL);
    node = ft_ast_simplecommand(token);
    if(node)
        return node;
    node = ft_ast_subshell(token);
    if(node)
    {
        while(ft_token_isredirect(token_type))
        {
            if((*token)->value == NULL)
                return ft_ast_free(node);
            ft_lstadd_back(&node->redirect,ft_lstnew(*token));
            *token = (*token)->next;
        }
        return node;
    }
    return node;
}


t_ast	*ft_ast_pipeline(t_token **token)
{
    t_token_type	token_type;
    t_ast			*node;
    t_list * lst;

    if (*token == NULL)
        return (NULL);
    node = ft_ast_command(token);
    if(node == NULL)
        return NULL;
    lst = ft_lstnew(node);
    node = ft_ast_new(AST_PIPELINE);
    ft_lstadd_back(&node->children, lst);
    while(1)
    {
        token_type = (*token)->type;
        if (token_type == TOKEN_EOI)
            break ;
        if (token_type == TOKEN_PIPE )
        {
            lst = ft_lstnew(ft_ast_new(AST_PIPE)); 
            ft_lstadd_back(&node->children, lst);
            *token = (*token)->next;
            node = ft_ast_command(token);
            if (node == NULL)
                return ft_ast_free(node);
        }
        else 
        return  ft_ast_free(node);
    }
    return node;
}

t_ast	*ft_ast_andor(t_token **token)
{
    t_token_type	token_type;
    t_ast			*node;
    t_list * lst;

    if (*token == NULL)
        return (NULL);
    node = ft_ast_pipeline(token);
    if (node == NULL)
        return (NULL);
    lst = ft_lstnew(node);
    node = ft_ast_new(AST_AND_OR);
    ft_lstadd_back(&node->children, lst);
    while (1)
    {
        token_type = (*token)->type;
        if (token_type == TOKEN_EOI)
            break ;
        if (token_type == TOKEN_OR || token_type == TOKEN_AND)
        {
            lst = ft_lstnew(ft_ast_new(ft_ast_fromtoken(token_type))); 
            ft_lstadd_back(&node->children, lst);
            *token = (*token)->next;
            node = ft_ast_pipeline(token);
            if (node == NULL)
                return ft_ast_free(node);
        }
        else 
        return  ft_ast_free(node);
    }
    return node;
}
