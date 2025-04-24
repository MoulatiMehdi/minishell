
#include "collector.h"
#include "tokenizer.h"

#define BALANCED "\033[1;32mBalanced\033[0m"
#define UNBALANCED "\033[1;31mUnbalanced\033[0m"

typedef struct s_input
{
	char	*str;
	int		expected;
}			t_input;



int	is_unbalance(const char *str);

int	test(char *input)
{
	t_token	*tokens;
	t_token	*tmp;

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
    return 0;
}

int	main()
{
	int	size;
	int	i;

	t_input inputs[] = {
		{
			.str = "'",
			.expected = 1,
		},
		{
			.str = "\"",
			.expected = 1,
		},
		{
			.str = "(",
			.expected = 1,
		},
		{
			.str = ")",
			.expected = 1,
		},
		{
			.str = "()",
			.expected = 1,
		},
		{
			.str = "(ls)",
			.expected = 0,
		},
		{
			.str = "(')",
			.expected = 1,
		},
		{
			.str = "(\')",
			.expected = 1,
		},
		{
			.str = "'\"'",
			.expected = 0,
		},
		{
			.str = "'\"'\"\"",
			.expected = 0,
		},
		{
			.str = "'\"'''",
			.expected = 0,
		},
		{
			.str = "'\"'",
			.expected = 0,
		},
		{
			.str = "''''''''''''",
			.expected = 0,
		},
		{
			.str = "\"\"\"\"\"\"\"\"\"\"",
			.expected = 0,
		},
		{
			.str = "'''''''''''",
			.expected = 1,
		},
		{
			.str = "\"\"\"\"\"\"\"\"\"",
			.expected = 1,
		},
		{
			.str = "\")))(((\"\"()\"\"\"\"\"\"",
			.expected = 1,
		},
		{
			.str = "\")))(((\"\"()\"\"\"\"\"",
			.expected = 0,
		},
		{
			.str = "\")))(((\"\"()\"()\"\"\"\"",
			.expected = 1,
		},
		{
			.str = "\")))(((\"\"()\"(ls)\"\"\"\"",
			.expected = 0,
		},
	};
	i = 0;
	size = sizeof(inputs) / sizeof(inputs[0]);
	close(2);
	while (i < size)
	{
		printf("Input : \033[1;33m%s\033[0m\n\n", inputs[i].str);
		printf("\texpected : %s\n", inputs[i].expected ? UNBALANCED : BALANCED);
		printf("\tresult   : %s\n\n",
			is_unbalance(inputs[i].str) ? UNBALANCED : BALANCED);
		printf("--------------------------\n");
		i++;
	}
	ft_clear();
	return (0);
}
