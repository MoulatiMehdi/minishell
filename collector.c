/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:12:31 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/16 19:52:56 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "collector.h"
#include "libft/libft.h"
#include <stdlib.h>

t_list	*g_head = NULL;

void	*ft_malloc(size_t size)
{
	void	*addr;
	t_list	*node;

	addr = malloc(size);
	if (addr == NULL)
		return (NULL);
	node = ft_lstnew(addr);
	if (node == NULL)
	{
		free(addr);
		return (NULL);
	}
	ft_lstadd_front(&g_head, node);
	return (node);
}

void	ft_free(void *addr)
{
	t_list	*node_curr;
	t_list	*node_prev;

	node_prev = NULL;
	node_curr = g_head;
	if (node_curr->content == addr)
	{
		g_head = node_curr->next;
		ft_lstdelone(node_curr, free);
		return ;
	}
	while (node_curr)
	{
		if (node_curr->content == addr)
		{
			node_prev->next = node_curr->next;
			ft_lstdelone(node_curr, free);
			break ;
		}
		node_prev = node_curr;
		node_curr = node_curr->next;
	}
}

int	ft_clear(void)
{
	ft_lstclear(&g_head, free);
	return (0);
}
