/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:31:18 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/25 16:31:18 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
#define EXPANSION_H

#include "parser.h"
#include "tokenizer.h"
#include "libft/libft.h"

void expand_ast(t_ast *node, int last_status);

void	ft_token_expand(t_token *token);
#endif
