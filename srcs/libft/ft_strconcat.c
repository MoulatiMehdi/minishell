/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:29:40 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/03 18:03:47 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strconcat(char **target, char const *str)
{
	char	*tmp;

	if (target == NULL || str == NULL)
		return ;
	tmp = *target;
	*target = ft_strjoin(*target, str);
	free(tmp);
}

void	ft_strnconcat(char **target, char const *str, size_t len)
{
	char	*tmp;

	if (target == NULL || str == NULL)
		return ;
	tmp = *target;
	*target = ft_strnjoin(*target, str, len);
	free(tmp);
}
