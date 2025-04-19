/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:52:38 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/19 16:06:16 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*ft_token_new(const char *value, size_t length)
{
	t_token	*token_new;

	token_new = malloc(sizeof(t_token));
	if (token_new == NULL)
		return (NULL);
	token_new->next = NULL;
	token_new->length = length;
	token_new->type = -1;
	token_new->value = value;
	return (token_new);
}

void	ft_token_push(t_token **head, t_token *new_elem)
{
	static t_token	*last = NULL;

	if (!head || !new_elem)
		return ;
	if (*head == NULL)
		*head = new_elem;
	else
		last->next = new_elem;
	last = new_elem;
}

void	ft_token_addeoi(t_token **head, t_token *token_curr)
{
	t_token	*token;

	if (token_curr)
		ft_token_push(head, token_curr);
	token = ft_token_new(NULL, 0);
	if (token == NULL)
		return ;
	token->type = TOKEN_EOI;
	ft_token_push(head, token);
}
