/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_diren.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:57:42 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/24 09:57:43 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include <dirent.h>

char	*ft_diren_getname(DIR *stream)
{
	struct dirent	*dir;

	dir = readdir(stream);
	if (dir == NULL)
		return (NULL);
	return (dir->d_name);
}

DIR	*ft_diren_open(char *path)
{
	if (path)
		return (opendir(path));
	else
		return (opendir("."));
}
