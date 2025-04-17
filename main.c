#include "collector.h"
#include <stdio.h>

int	main(void)
{
	char	*str[100];
	int		j;
	int		len;
	int		size;

	ft_free(NULL);
	len = 100;
	size = sizeof(str) / sizeof(char *);
	for (int i = 0; i < size; i++)
	{
		str[i] = ft_malloc(len + 1);
		j = 0;
		for (j = 0; j < len; j++)
		{
			str[i][j] = 'A' + i;
		}
		str[i][j] = '\0';
	}
	ft_free(NULL);
	ft_free(str[10]);
	ft_free(NULL);
	/*for (int i = 0; i < size; i++)*/
	/*{*/
	/*	printf("%s\n", str[i]);*/
	/*}*/
	ft_clear();
	return (0);
}
