/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:59:27 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/26 17:35:31 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_valid_var_name(char c)
{
	return (c == '_' || ft_isalpha(c));
}

int	is_valid_char(char c)
{
	return (c == '_' || ft_isalnum(c));
}

int	is_valid_identifier(const char *var)
{
	int	i;

	if (!var || var[0] == '\0')
		return (0);
	if (!is_valid_var_name(var[0]))
		return (0);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!is_valid_char(var[i]))
			return (0);
		i++;
	}
	return (1);
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
	ft_putstr_fd(SHELL_NAME "export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": not a valid identifier", 2);
}
