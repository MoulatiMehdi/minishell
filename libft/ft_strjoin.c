/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:17:08 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/03 17:40:15 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1UL));
	if (!p)
		return (NULL);
	p[s1_len + s2_len] = 0;
	while (s2_len--)
		p[s1_len + s2_len] = s2[s2_len];
	while (s1_len--)
		p[s1_len] = s1[s1_len];
	return (p);
}

char	*ft_strnjoin(char const *s1, char const *s2, size_t len)
{
	char	*p;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s2_len > len)
		s2_len = len;
	p = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1UL));
	if (!p)
		return (NULL);
	p[s1_len + s2_len] = 0;
	while (s2_len--)
		p[s1_len + s2_len] = s2[s2_len];
	while (s1_len--)
		p[s1_len] = s1[s1_len];
	return (p);
}

char	*ft_strjoin_track(char const *s1, char const *s2)
{
	char	*p;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	p = (char *)ft_malloc(sizeof(char) * (s1_len + s2_len + 1UL));
	if (!p)
		return (NULL);
	p[s1_len + s2_len] = 0;
	while (s2_len--)
		p[s1_len + s2_len] = s2[s2_len];
	while (s1_len--)
		p[s1_len] = s1[s1_len];
	return (p);
}

char	*ft_strnjoin_track(char const *s1, char const *s2, size_t len)
{
	char	*p;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s2_len > len)
		s2_len = len;
	p = (char *)ft_malloc(sizeof(char) * (s1_len + s2_len + 1UL));
	if (!p)
		return (NULL);
	p[s1_len + s2_len] = 0;
	while (s2_len--)
		p[s1_len + s2_len] = s2[s2_len];
	while (s1_len--)
		p[s1_len] = s1[s1_len];
	return (p);
}
