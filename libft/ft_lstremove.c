/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@1337.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:44:49 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/24 17:50:18 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstremove_front(t_list **head, void *content)
{
	t_list	*curr;

	if (!head || !*head)
		return ;
	curr = *head;
	while (curr && content == curr->content)
	{
		*head = curr->next;
		free(curr);
		curr = *head;
	}
}

void	ft_lstremove(t_list **head, void *content)
{
	t_list	*curr;
	t_list	*prev;

	if (!head || !*head)
		return ;
	ft_lstremove_front(head, content);
	if (!head)
		return ;
	curr = *head;
	while (curr)
	{
		if (content == curr->content)
		{
			prev->next = curr->next;
			free(curr);
		}
		else
			prev = curr;
		curr = prev->next;
	}
	free(content);
}
