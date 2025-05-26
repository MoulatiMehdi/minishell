/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:39:54 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/26 11:38:00 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_unset_var(char *var, t_array *env)
{
	t_list	*curr;
	t_list	*prev;

	if (!var || !env || !env->head)
		return ;
	curr = ft_get_env(var, env);
	if (!curr)
		return ;
	prev = env->head;
	if (prev == curr)
	{
		env->head = curr->next;
	}
	else
	{
		while (prev->next && prev->next != curr)
			prev = prev->next;
		if (prev->next == curr)
			prev->next = curr->next;
	}
	free(curr->content);
	free(curr);
}

int	unset_cmd(char **args)
{
	int		i;
	t_array	*env;

	env = ft_env_get();
	if (!args || !args[0])
	{
		return (0);
	}
	i = 0;
	while (args[i])
	{
		ft_unset_var(args[i], env);
		i++;
	}
	return (0);
}
