/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:01:54 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/28 10:25:31 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft/libft.h"

static void	print_env(t_array *env)
{
	t_list	*curr;
	char	*str;

	if (!env)
		return ;
	curr = env->head;
	while (curr)
	{
		str = ft_strchr((char *)curr->content, '=');
		if (str && str[1] == '\0')
			;
		else if (str && ft_putendl_fd((char *)curr->content, 1) < 0)
		{
			perror(SHELL_NAME ": env: write error");
			break ;
		}
		curr = curr->next;
	}
}

int	env_cmd(char **args)
{
	t_array	*env;

	env = ft_env_get();
	if (!env)
		return (1);
	if (args && args[0])
	{
		ft_putendl_fd(SHELL_NAME ": env: too many arguments", 2);
		return (1);
	}
	print_env(env);
	return (0);
}
