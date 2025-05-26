/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:07:58 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/26 11:36:25 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_add_env(char *key, char *value, t_array *env)
{
	char	*prefix;
	char	*kv;

	if (!key || !value)
		return ;
	prefix = ft_strjoin(key, "=");
	free(key);
	kv = ft_strjoin(prefix, value);
	free(prefix);
	free(value);
	ft_array_push(&env, kv);
}

void	ft_update_env(char *key, char *value, t_array *env)
{
	t_list	*node;
	char	*prefix;
	char	*new_var;

	if (!key || !value || !env)
		return ;
	node = ft_get_env(key, env);
	if (node)
	{
		prefix = ft_strjoin(key, "=");
		if (!prefix)
		{
			free(key);
			free(value);
			return ;
		}
		new_var = ft_strjoin(prefix, value);
		free(prefix);
		free(node->content);
		node->content = new_var;
		free(key);
		free(value);
	}
	else
		ft_add_env(key, value, env);
}

int	ft_is_var_exist(char *var, t_array *env)
{
	char	*key;
	t_list	*node;
	int		exists;

	if (!var || !env)
		return (1);
	key = get_var_key(var);
	if (!key)
		return (1);
	node = ft_get_env(key, env);
	exists = (node == NULL);
	free(key);
	return (exists);
}

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
			value = get_var_value(args[i]);
			if (!value)
				value = ft_strdup("");
			if (ft_is_var_exist(args[i], env))
				ft_add_env(key, value, env);
			else
				ft_update_env(key, value, env);
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
