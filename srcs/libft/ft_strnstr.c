/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:17:09 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/10 11:30:24 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!haystack || !needle)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		while (i + j < len && needle[j] && haystack[i + j])
		{
			if (needle[j] != haystack[i + j])
				break ;
			j++;
		}
		if (!needle[j])
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}

char	*ft_strstr(char *str, char *to_find)
{
	size_t	i;
	size_t	j;

	if (!*to_find)
		return (str);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (to_find[j] && to_find[j] == str[i + j])
			j++;
		if (!to_find[j])
			return (str + i);
		i++;
	}
	return (0);
}
