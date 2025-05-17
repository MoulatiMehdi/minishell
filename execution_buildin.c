/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_buildin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:37:11 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/16 18:37:12 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_command_isbuildin(char *str)
{
	size_t		i;
	static char	*buildins[] = {"echo", "env", "pwd", "unset", "export", "cd",
		"exit", NULL};

	i = 0;
	while (buildins[i])
	{
		if (strcmp(buildins[i], str) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_execute_buildin(t_list *redirect, char **args)
{
	ft_putstr_fd("\033[1;93m======= UNDER DEVOLOPEMENT =======\033[0m\n", 1);
	return (0);
}
