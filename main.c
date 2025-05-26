/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:09:35 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/12 23:39:06 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "execution.h"
#include "status.h"

void	debug(t_ast *node)
{
	printf("\n*******************************************\n");
	printf("\t ABSTRACT SYNTAX TREE \n");
	printf("\t========================\n");
	ft_ast_print(node, 0);
	printf("\n*******************************************\n");
	printf("\t  COMMAND FROM AST \n");
	printf("\t====================\n");
	ft_ast_tocommand(node);
	printf("\n");
}

int	main(void)
{
	if (ft_shell_isinteractive())
		ft_shell_interactive();
	else
		ft_shell_noninteractive();
	return (ft_status_get());
}
