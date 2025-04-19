#include <string.h>

int	ft_str_isoperator(const char *str)
{
	size_t				i;
	static const char	*operators[] = {">>", "<<", "||", "&&", 0};

	i = 0;
	while (operators[i])
	{
		if (strncmp(str, operators[i], 2) == 0)
			return (1);
		i++;
	}
	return (0);
}
