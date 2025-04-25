#ifndef DEBUG_H

#include "parser.h"
#include <string.h>
#include "collector.h"
#include "lexer.h"
#include "tokenizer.h"
#include "parser.h"
#include <readline/readline.h>
#include <readline/rlstdc.h>
#include <stdio.h>
#include <unistd.h>

void ft_ast_tocommand(t_ast * ast);
void ft_list_tokens_print(t_list * head);
void ft_ast_print(t_ast * ast,int depth);
char	*ft_token_type(t_token *token);
void ft_lexer_print(t_token * token);

#endif // !DEBUG_H
