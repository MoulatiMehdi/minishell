/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:21:14 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/27 08:21:14 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		free(curr);
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
			free(curr);
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
