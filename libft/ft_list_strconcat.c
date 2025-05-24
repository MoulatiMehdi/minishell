/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_strconcat.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 14:58:27 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/24 14:58:27 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_list_strconcat(t_list *list, char *str)
{
	if (list == NULL || str == NULL)
		return ;
	while (list)
	{
		ft_strconcat((char **)&list->content, str);
		list = list->next;
	}
}
