/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:23:37 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/21 18:17:18 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_PIPE,
	TOKEN_PARENS_OPEN,
	TOKEN_PARENS_CLOSE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_REDIRECT_HERE,
	TOKEN_EOI,
}					t_token_type;

typedef struct s_token
{
	const char		*value;
	t_token_type	type;
	size_t			length;
	struct s_token	*next;
}					t_token;

t_token				*tokenize(const char *line);
int					ft_token_isredirect(t_token_type type);

#endif
