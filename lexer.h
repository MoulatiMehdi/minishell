/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:55:17 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/27 08:53:09 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# define MAX_HEREDOC 16
# define ERR_HEREDOC_LIMIT "bash: maximum here-document count exceeded\n"

# include "status.h"
# include "tokenizer.h"

void	lexer(t_token *token);
#endif // !LEXER_H
