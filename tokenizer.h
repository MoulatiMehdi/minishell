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
	char *value;
	t_token_type type;
	int length;
	struct s_token *next;
} t_token;

typedef enum e_state
{
	STATE_NONE,
	STATE_WORD,
	STATE_OPERATOR
} t_state;

#endif