/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:12:31 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/16 16:12:31 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./garbge_collector.h"
#include <stdlib.h>

void	*ft_malloc(size_t size)
{
	return (malloc(size));
}

void	ft_free(void *addr)
{
	free(addr);
}

int	ft_clear(void)
{
	return (0);
}
