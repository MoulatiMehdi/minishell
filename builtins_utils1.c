/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:59:27 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/28 12:46:52 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_var_value(const char *var)
{
	const char	*eq = ft_strchr(var, '=');
	if (!eq)
		return (NULL);
	return (ft_strdup(eq + 1));
}

int	print_export(t_array *env)
{
	t_list	*curr;

	if (!env)
		return (1);
	curr = env->head;
	while (curr)
	{
		printf("declare -x %s\n", (char *)curr->content);
		curr = curr->next;
	}
	return (0);
}

void	print_export_error(char *arg)
{
	if (!arg)
		return ;
	ft_putstr_fd(SHELL_NAME ": export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": not a valid identifier", 2);
}
