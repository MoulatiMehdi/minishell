/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:31:52 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/15 14:11:15 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	*ft_get_env(char *key, t_array *env)
{
	int		size;
	t_list	*curr;
	char	*entry;

	if (env == NULL || key == NULL)
		return (NULL);

	size = ft_strlen(key);
	curr = env->head;

	while (curr)
	{
		entry = (char *)curr->content;
		if (ft_strncmp(entry, key, size) == 0 && entry[size] == '=')
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

char *get_var_key(char *var)
{
    int i;
    char *key;

    if (!var)
        return (NULL);
    i = 0;
    while (var[i] && var[i] != '=')
        i++;
    key = malloc(i + 1);
    if (!key)
        return (NULL);
    memcpy(key, var, i);
    key[i] = '\0';
    return (key);
}

char *get_var_value(const char *var)
{
    const char *eq = ft_strchr(var, '=');
    if (!eq)
        return (NULL);
    return ft_strdup(eq + 1);
}

void	compute_limit(int sign, unsigned long *limit)
{
	if (sign >= 0)
		*limit = (unsigned long)LONG_MAX;
	else
		*limit = (unsigned long)LONG_MAX + 1UL;
}