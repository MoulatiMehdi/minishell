/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:18:10 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/27 10:52:45 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_array	*ft_array_new(void)
{
	t_array	*array;

	array = malloc(sizeof(t_array));
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

void	ft_array_destroy(t_array **array, t_func_free free_fct)
{
	if (array == NULL || *array == NULL)
		return ;
	ft_lstclear(&(*array)->head, free_fct);
	free(*array);
	*array = NULL;
}

t_array	*ft_tracked_array_new(void)
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

void	*ft_tracked_array_push(t_array **array, void *content)
{
	t_list	*node;

	if (array == NULL || content == NULL)
		return (NULL);
	node = ft_lstnew(content);
	ft_collector_track(node);
	if (node == NULL)
		return (NULL);
	if (*array == NULL)
		*array = ft_tracked_array_new();
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
