/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:31:18 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/07 13:30:42 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
#define EXPANSION_H

#include "parser.h"
#include "tokenizer.h"
#include "libft/libft.h"

void expand_ast(t_ast *node, int last_status);
void expand_token(t_token *token);

#endif