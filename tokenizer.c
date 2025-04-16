#include "tokenizer.h"

int is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

int is_double_operator(const char *str, int length)
{
	static const char *operators[] = {
		">>",
		"<<",
		"||",
		"&&",
		NULL};
	int i = 0;
	while (operators[i])
	{
		if (strncmp(str, operators[i], length) == 0)
			return 1;
		i++;
	}
	return 0;
}

void add_token(t_token **head, const char *start, int len)
{
	t_token *new = malloc(sizeof(t_token));
	new->value = start;
	new->length = len;
	new->type = -1;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		t_token *tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int collect_quoted(const char *line, int i, char quote, const char **out)
{
	int start = i++;
	while (line[i] && line[i] != quote)
		i++;
	if (!line[i])
		return -1;
	*out = &line[start];
	return i - start + 1;
}

t_token *tokenize(const char *line)
{
	t_token *head = NULL;
	t_state state = STATE_NONE;
	int token_start = 0;
	int i = 0;
	char curr;

	while (line[i])
	{
		curr = line[i];

		if (state == STATE_OPERATOR && is_double_operator(line + token_start, 2))
		{
			add_token(&head, &line[token_start], 2);
			i++;
			state = STATE_NONE;
			continue;
		}
		if (state == STATE_OPERATOR)
		{
			add_token(&head, &line[token_start], 1);
			state = STATE_NONE;
			continue;
		}

		if (curr == '\'' || curr == '"')
		{
			if (state == STATE_WORD)
			{
				add_token(&head, &line[token_start], i - token_start);
				state = STATE_NONE;
			}
			const char *quoted;
			int len = collect_quoted(line, i, curr, &quoted);
			if (len == -1)
			{
				printf("Error: quote not closed\n");
				return NULL;
			}
			add_token(&head, quoted, len);
			i += len;
			continue;
		}

		if (is_operator_char(curr))
		{
			if (state == STATE_WORD)
			{
				add_token(&head, &line[token_start], i - token_start);
				state = STATE_NONE;
			}
			token_start = i;
			state = STATE_OPERATOR;
			i++;
			continue;
		}

		if (curr == ' ' || curr == '\t')
		{
			if (state == STATE_WORD)
			{
				add_token(&head, &line[token_start], i - token_start);
				state = STATE_NONE;
			}
			i++;
			continue;
		}

		if (state == STATE_WORD)
		{
			i++;
			continue;
		}

		token_start = i;
		state = STATE_WORD;
		i++;
	}

	if (state == STATE_WORD)
		add_token(&head, &line[token_start], i - token_start);
	else if (state == STATE_OPERATOR)
		add_token(&head, &line[token_start], 1);

	return head;
}

int main(void)
{
	const char *input = "echo \"'nested' \"quotes\"\" 'a\"b\"c' \"a'b'c\"";
	t_token *tokens = tokenize(input);
	t_token *tmp = tokens;

	printf("Input: %s\n\n", input);
	printf("Tokens:\n");
	while (tmp)
	{
		printf(" - %-20.*s | Length: %2d\n",
			   (int)tmp->length, tmp->value, (int)tmp->length);
		tmp = tmp->next;
	}
	return 0;
}
