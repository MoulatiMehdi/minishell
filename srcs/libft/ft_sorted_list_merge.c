/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorted_list_merge.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@1337.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:44:14 by mmoulati          #+#    #+#             */
/*   Updated: 2024/09/12 18:22:36 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_list_skip(t_list **prev, t_list *curr, t_list **head2,
		int (*cmp)(void *content1, void *content2))
{
	t_list	*tmp;

	if (!cmp || !head2 || !*head2)
		return ;
	while (curr && (*head2)->next && (*cmp)((*head2)->next->content,
		curr->content) <= 0)
		*head2 = (*head2)->next;
	*prev = *head2;
	tmp = (*head2)->next;
	(*head2)->next = curr;
	*head2 = tmp;
}

void	ft_sorted_list_merge(t_list **head1, t_list *head2,
		int (*cmp)(void *content1, void *content2))
{
	t_list	*curr;
	t_list	*prev;

	if (!head2 || !cmp)
		return ;
	if (!head1 || !*head1)
	{
		*head1 = head2;
		return ;
	}
	curr = *head1;
	prev = 0;
	while (head2)
	{
		while (curr && (*cmp)(curr->content, head2->content) < 0)
		{
			prev = curr;
			curr = curr->next;
		}
		if (prev)
			prev->next = head2;
		else
			*head1 = head2;
		ft_list_skip(&prev, curr, &head2, cmp);
	}
}
