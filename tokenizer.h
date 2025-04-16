#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_QUOTED_STRING
} t_token_type;

typedef struct s_token
{
	const char *value;
	t_token_type type;
	size_t length;
	struct s_token *next;
} t_token;

typedef enum e_state
{
	STATE_NONE,
	STATE_WORD,
	STATE_OPERATOR
} t_state;

t_token *tokenize(const char *line);
void add_token(t_token **head, const char *start, int len);
int is_double_operator(const char *str, int length);
int is_operator_char(char c);

#endif