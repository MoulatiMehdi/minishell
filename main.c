#include "execution.h"
#include "status.h"

// void	debug(t_ast *node)
// {
// 	printf("\n*******************************************\n");
// 	printf("\t ABSTRACT SYNTAX TREE \n");
// 	printf("\t========================\n");
// 	ft_ast_print(node, 0);
// 	printf("\n*******************************************\n");
// 	printf("\t  COMMAND FROM AST \n");
// 	printf("\t====================\n");
// 	ft_ast_tocommand(node);
// 	printf("\n");
// }

bool	ft_shell_isinteractive(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDERR_FILENO));
}

int	main(void)
{
	if (ft_shell_isinteractive())
		ft_shell_interactive();
	else
		ft_shell_noninteractive();
	return (ft_status_get());
}