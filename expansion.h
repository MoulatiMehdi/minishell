/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:31:18 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/17 18:16:07 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "libft/libft.h"
# include "parser.h"
# include "tokenizer.h"
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>

# define IFS "\n\t "

void	expand_token(t_token *token);
void join_quotes(t_word *head);
t_array* field_splitting(t_word *word);
void pathname_expansion(t_token *token,t_array * fields);
void expand_param(t_word *word);

#endif
