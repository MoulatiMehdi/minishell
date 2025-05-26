/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorted_list_insert.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@1337.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:44:24 by mmoulati          #+#    #+#             */
/*   Updated: 2024/09/13 19:34:41 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sorted_list_insert(t_list **begin_list, void *content,
		int (*cmp)(void *s1, void *s2))
{
	t_list	*new_elem;
	t_list	*prev;
	t_list	*curr;

	if (!begin_list)
		return ;
	new_elem = ft_lstnew(content);
	if (!new_elem || !cmp)
		return ;
	if (!*begin_list)
		return ((void)(*begin_list = new_elem));
	prev = 0;
	curr = *begin_list;
	while (curr && (*cmp)(curr->content, content) < 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev)
		*begin_list = new_elem;
	else
		prev->next = new_elem;
	new_elem->next = curr;
}
