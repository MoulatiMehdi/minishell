/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:17:07 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/10 11:31:28 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strndup(const char *src, size_t n)
{
	char	*p;
	size_t	size;
	size_t	i;

	i = 0;
	if (src == NULL)
		return (0);
	size = ft_strlen(src);
	if (n < size)
		size = n;
	p = (char *)malloc((size + 1) * sizeof(char));
	if (p == NULL)
		return (0);
	while (i < size)
	{
		p[i] = src[i];
		i++;
	}
	p[size] = '\0';
	return (p);
}
