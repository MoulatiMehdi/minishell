/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@1337.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:44:49 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/26 17:16:16 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_list_remove_front_if(t_list **head, void *content,
		t_func_cmp cmp, t_func_free free_fct)
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

void	ft_list_remove_if(t_list **head, void *content, t_func_cmp cmp,
		t_func_free free_fct)
{
	t_list	*curr;
	t_list	*prev;

	if (!head || !*head || !cmp)
		return ;
	ft_list_remove_front_if(head, content, cmp, free_fct);
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
