/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:07:58 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/28 10:38:09 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	process_export_args(char **args, t_array *env, int *status)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			print_export_error(args[i]);
			*status = 1;
		}
		else
		{
			key = get_var_key(args[i]);
			value = ft_env_getvalue(key);
			ft_env_set(key, value);
			free(key);
		}
		i++;
	}
}

int	export_cmd(char **args)
{
	int		status;
	t_array	*env;

	env = ft_env_get();
	status = 0;
	if (!args || !args[0])
		return (print_export(env));
	process_export_args(args, env, &status);
	return (status);
}
