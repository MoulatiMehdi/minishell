/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:12:31 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/24 17:57:25 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	**ft_collecter_get(void)
{
	static t_list	*g_head = NULL;

	return (&g_head);
}

void	*ft_collector_track(void *addr)
{
	t_list	*node;
	t_list	**header;

	node = ft_lstnew(addr);
	header = ft_collecter_get();
	if (node == NULL)
	{
		free(addr);
		return (NULL);
	}
	if (header)
		node->next = *header;
	*header = node;
	return (addr);
}

void	*ft_malloc(size_t size)
{
	void	*addr;

	addr = malloc(size);
	if (addr == NULL)
		return (NULL);
	return (ft_collector_track(addr));
}

void	ft_free(void *addr)
{
	t_list	*node_curr;
	t_list	*node_prev;
	t_list	**header;

	header = ft_collecter_get();
	if (header == NULL || addr == NULL)
		return ;
	ft_lstremove(header, addr);
}

int	ft_clear(void)
{
	t_list	**header;

	header = ft_collecter_get();
	ft_lstclear(header, free);
	return (0);
}
