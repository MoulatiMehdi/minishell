/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:02:29 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/27 14:47:17 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

static char	*status_to_str(void)
{
	static char		buf[4];
	unsigned char	s;
	int				len;

	s = ft_status_get();
	len = 0;
	if (s >= 100)
	{
		buf[len++] = '0' + (s / 100);
		buf[len++] = '0' + ((s / 10) % 10);
		buf[len++] = '0' + (s % 10);
	}
	else if (s >= 10)
	{
		buf[len++] = '0' + (s / 10);
		buf[len++] = '0' + (s % 10);
	}
	else
	{
		buf[len++] = '0' + s;
	}
	buf[len] = '\0';
	return (buf);
}

char	*ft_env_getvaluebysubstr(char *key, size_t length)
{
	t_array	*array;
	t_list	*lst;
	char	*p;

	array = ft_env_get();
	if (array == NULL || key == NULL)
		return (NULL);
	if (ft_strncmp(key, "?", length) == 0)
		return (status_to_str());
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
	size_t	len;

	if (key == NULL)
		return (NULL);
	len = ft_strlen(key);
	return (ft_env_getvaluebysubstr(key, len));
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
	ft_memcpy(&str[len1 + 1], value, len2);
	str[len1 + len2 + 1] = '\0';
	ft_array_push(ft_env_ptr(), str);
	return (str);
}
