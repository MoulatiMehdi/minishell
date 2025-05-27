#ifndef DEBUG_H

#include "parser.h"
#include <string.h>
#include <readline/readline.h>
#include <readline/rlstdc.h>
#include <stdio.h>
#include <unistd.h>

char * ft_asttype_getstr(t_token_type type);
void ft_ast_tocommand(t_ast * ast);
void ft_list_tokens_print(t_list * head);
void ft_ast_print(t_ast * ast,int depth);
char	*ft_token_type(t_token *token);
void ft_lexer_print(t_token * token);
void ft_ast_expansion(t_ast * ast,int depth);

#endif // !DEBUG_H
