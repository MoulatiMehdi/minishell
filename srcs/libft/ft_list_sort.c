/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@1337.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:44:39 by mmoulati          #+#    #+#             */
/*   Updated: 2024/09/12 14:26:20 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_list_swap_items(t_list *p_prev, t_list **p, t_list *q_prev,
		t_list **q)
{
	t_list	*tmp;

	if (!q || !p || !*q || !*p || p == q)
		return ;
	if (p_prev)
		p_prev->next = *q;
	if (q_prev)
		q_prev->next = *p;
	tmp = (*q)->next;
	(*q)->next = (*p)->next;
	(*p)->next = tmp;
	tmp = *p;
	*p = *q;
	*q = tmp;
}

static void	next_item(t_list **p_prev, t_list **p, t_list *value)
{
	if (!p || !p_prev)
		return ;
	*p_prev = value;
	if (value)
		*p = value->next;
}

void	ft_list_sort(t_list **begin_list, int (*cmp)(void *s1, void *s2))
{
	t_list	*p;
	t_list	*q;
	t_list	*p_prev;
	t_list	*q_prev;

	if (!cmp || !begin_list || !*begin_list)
		return ;
	p = *begin_list;
	p_prev = 0;
	while (p->next)
	{
		next_item(&q_prev, &q, p);
		while (q)
		{
			if ((*cmp)(p->content, q->content) > 0)
			{
				ft_list_swap_items(p_prev, &p, q_prev, &q);
				if (!p_prev)
					*begin_list = p;
			}
			next_item(&q_prev, &q, q);
		}
		next_item(&p_prev, &p, p);
	}
}
