/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:17:06 by mmoulati          #+#    #+#             */
/*   Updated: 2025/02/10 11:32:55 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	size;

	if (!s || fd < 0)
		return (0);
	size = ft_putstr_fd(s, fd);
	if (size < 0 || write(fd, "\n", 1) < 0)
		return (-1);
	return (size + 1);
}
