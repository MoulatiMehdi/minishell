/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:02:29 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/27 08:34:22 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <string.h>

char	*ft_env_getvaluebysubstr(char *key, size_t length)
{
	t_array	*array;
	t_list	*lst;
	char	*p;

	array = ft_env_get();
	if (array == NULL || key == NULL)
		return (NULL);
	lst = array->head;
	while (lst)
	{
		p = lst->content;
		if (ft_strncmp(key, p, length) == 0 && p[length] == '=')
			return (&p[length + 1]);
		lst = lst->next;
	}
	return (NULL);
}

char	*ft_env_getvalue(char *key)
{
	t_array	*array;
	t_list	*lst;
	char	*p;
	size_t	len;

	array = ft_env_get();
	if (array == NULL || key == NULL)
		return (NULL);
	lst = array->head;
	len = ft_strlen(key);
	while (lst)
	{
		p = lst->content;
		if (ft_strncmp(key, p, len) == 0 && p[len] == '=')
			return (&p[len + 1]);
		lst = lst->next;
	}
	return (NULL);
}

int	ft_keycmp(char *key, char *key_env)
{
	size_t	len;

	len = ft_strlen(key);
	return (ft_strncmp(key, key_env, len) || key_env[len] != '=');
}

char	*ft_env_set(char *key, char *value)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (key == NULL)
		return (NULL);
	ft_array_remove(ft_env_ptr(), key, (t_func_cmp)ft_keycmp, free);
	len1 = ft_strlen(key);
	len2 = ft_strlen(value);
	str = malloc(sizeof(char) * (len1 + len2 + 2UL));
	ft_memcpy(str, key, len1);
	str[len1] = '=';
	ft_memcpy(&str[len1 + 1], value, len1 + len2 + 1);
	str[len1 + len2 + 1] = '\0';
	ft_array_push(ft_env_ptr(), str);
	return (str);
}
