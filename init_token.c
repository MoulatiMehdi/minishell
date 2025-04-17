/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:52:38 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/17 12:56:09 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	init_token(t_tokenizer *t, const char *line)
{
	t->line = line;
	t->i = 0;
	t->start = 0;
	t->state = STATE_NONE;
	t->head = NULL;
	t->last = NULL;
}
