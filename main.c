#include "tokenizer.h"
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	t_token	*tokens;
	t_token	*tmp;
	char	*input;

	if (argc != 2)
		return (-1);
	input = argv[1];
	printf("Input:\t %s\n\n", input);
	printf("Output:\n");
	tokens = tokenize(input);
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_EOI)
			printf("\tEND_OF_INPUT\n");
		else
			printf("\t%s\n", strndup(tmp->value, tmp->length));
		tmp = tmp->next;
	}
	return (0);
}
