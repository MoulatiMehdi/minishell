/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:12:31 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/17 11:55:13 by mmoulati         ###   ########.fr       */
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
	return (node);
}

void	*ft_malloc(size_t size)
{
	void	*addr;
	t_list	*node;
	t_list	**header;

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
	node_prev = NULL;
	node_curr = *header;
	if (node_curr->content == addr)
	{
		*header = node_curr->next;
		return (ft_lstdelone(node_curr, free));
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
	t_list	**header;

	header = ft_collecter_get();
	ft_lstclear(header, free);
	return (0);
}
