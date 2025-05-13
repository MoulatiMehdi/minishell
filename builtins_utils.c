/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:31:52 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/13 13:00:17 by okhourss         ###   ########.fr       */
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