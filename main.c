
#include "collector.h"
#include "tokenizer.h"

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
			printf("\t- EOF\n");
		else
			printf("\t- %-40.*s | Length: %2d\n", (int)tmp->length, tmp->value,
				(int)tmp->length);
		tmp = tmp->next;
	}
	ft_clear();
	return (0);
}
