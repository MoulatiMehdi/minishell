/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:05:04 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/13 16:36:32 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char *get_var_key(char *var)
{
	if (!var)
		return (NULL);
	int i = 0;
	char *key;
	key = NULL;
	while (var[i])
	{
		if (var[i] == '=')
		{
			ft_strnconcat(&key,var,i);
			break;
		}
		i++;
	}
	return (key);
}

int ft_is_var_exist(char *var)
{
	if (!var)
		return 1;
	char *key = get_var_key(var);
	if (!key)
		return 1;
	return 0;
}

int export_cmd(t_cmd *cmd)
{
	if (!cmd)
		return (1);
	if (!cmd->args)
	{
		// not sure if we need to print all vars or not
		ft_putendl_fd("usage: export <var_name>=<var_value>",2);
		return 1;
	}
	// need to loop over all the args and add them to env
	int i = 0;
	while (cmd->args[i])
	{
		if (ft_is_var_exist(cmd->args[i]))
		{
			//var not exist need to be added
			printf("\nthis var `%s` is not exist\n",cmd->args[i]);
		}
		else{
			printf("\nthis var `%s` exist\n",cmd->args[i]);
		}
		i++;
	}
	return 0;
}
