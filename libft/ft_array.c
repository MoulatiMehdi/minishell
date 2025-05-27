/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:18:10 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/26 15:50:00 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_array	*ft_array_new(void)
{
	t_array	*array;

	array = ft_malloc(sizeof(t_array));
	if (array == NULL)
		return (NULL);
	array->head = NULL;
	array->last = NULL;
	array->length = 0;
	return (array);
}

void	*ft_array_push(t_array **array, void *content)
{
	t_list	*node;

	if (array == NULL || content == NULL)
		return (NULL);
	node = ft_lstnew(content);
	ft_collector_track(node);
	if (node == NULL)
		return (NULL);
	if (*array == NULL)
		*array = ft_array_new();
	if (*array == NULL)
	{
		free(node);
		return (NULL);
	}
	if ((*array)->head == NULL)
		(*array)->head = node;
	if ((*array)->last != NULL)
		(*array)->last->next = node;
	(*array)->last = ft_lstlast(node);
	(*array)->length++;
	return (content);
}

static void	ft_array_listremovefront(t_list **head, void *content,
		int (*cmp)(void *, void *), void (*free_fct)(void *))
{
	t_list	*curr;

	if (!head || !*head || !cmp)
		return ;
	curr = *head;
	while (curr && (*cmp)(content, curr->content) == 0)
	{
		if (free_fct)
			free_fct(curr->content);
		*head = curr->next;
		ft_free(curr);
		curr = *head;
	}
}

static void	ft_array_listremove(t_list **head, void *content, t_func_cmp cmp,
		void (*free_fct)(void *))
{
	t_list	*curr;
	t_list	*prev;

	if (!head || !*head || !cmp)
		return ;
	ft_array_listremovefront(head, content, cmp, free_fct);
	if (!head)
		return ;
	curr = *head;
	while (curr)
	{
		if ((*cmp)(content, curr->content) == 0)
		{
			if (free_fct)
				free_fct(curr->content);
			prev->next = curr->next;
			ft_free(curr);
		}
		else
			prev = curr;
		curr = prev->next;
	}
}

void	ft_array_remove(t_array **array, void *content, t_func_cmp cmp,
		t_func_free del)
{
	if (array == NULL || *array == NULL || cmp == NULL)
		return ;
	ft_array_listremove(&(*array)->head, content, cmp, del);
	(*array)->last = ft_lstlast((*array)->head);
	(*array)->length = ft_lstsize((*array)->head);
}
