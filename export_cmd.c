/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:07:58 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/28 12:37:54 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


static int	is_valid_var_name(char c)
{
	return (c == '_' || ft_isalpha(c));
}

static int	is_valid_char(char c)
{
	return (c == '_' || ft_isalnum(c));
}
static int	is_valid_identifier(const char *var)
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
static void	process_export_args(char **args, int *status)
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
	process_export_args(args, &status);
	return (status);
}
