/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:52:38 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/18 13:21:56 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdlib.h>

void	init_token(t_tokenizer *t, const char *line)
{
	t->line = line;
	t->i = 0;
	t->start = 0;
	t->state = STATE_NONE;
	t->head = NULL;
	t->last = NULL;
}

t_token	*ft_token_new(const char *value, size_t length)
{
	t_token	*token_new;

	token_new = malloc(sizeof(t_token *));
	token_new->next = NULL;
	token_new->length = length;
	token_new->type = -1;
	token_new->value = value;
	return (token_new);
}

void	ft_token_push(t_token **head, t_token *new_elem)
{
	t_token	*p;

	if (!head || !new_elem)
		return ;
	if (*head == NULL)
	{
		*head = new_elem;
		return ;
	}
	p = *head;
	while (p->next)
		p = p->next;
	p->next = new_elem;
}

void	ft_token_addeoi(t_token **head)
{
	t_token	*token;

	token = ft_token_new(NULL, 0);
	if (token == NULL)
		return ;
	token->type = TOKEN_EOI;
	ft_token_push(head, token);
}
