/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getvalue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:02:29 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/26 19:02:29 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**ft_env_strs(void)
{
	t_array	*array;
	char	**strs;
	t_list	*lst;
	size_t	i;

	array = ft_env_get();
	if (!array || array->length == 0)
		return (NULL);
	strs = ft_malloc((sizeof(char *) + 1) * array->length);
	lst = array->head;
	i = 0;
	while (lst)
	{
		strs[i] = lst->content;
		lst = lst->next;
		i++;
	}
	return (strs);
}

char	*ft_env_valuebysubkey(char *key, size_t length)
{
	t_array	*array;
	t_list	*lst;
	char	*p;

	array = ft_env_get();
	lst = array->head;
	while (lst)
	{
		p = lst->content;
		if (ft_strncmp(key, p, length) && p[length] == '=')
			return (&p[length + 1]);
		lst = lst->next;
	}
	return (NULL);
}

char	*ft_env_value(char *key)
{
	t_array	*array;
	t_list	*lst;
	char	*p;
	size_t	len;

	array = ft_env_get();
	lst = array->head;
	len = ft_strlen(key);
	while (lst)
	{
		p = lst->content;
		if (ft_strncmp(key, p, len) && p[len] == '=')
			return (&p[len + 1]);
		lst = lst->next;
	}
	return (NULL);
}
