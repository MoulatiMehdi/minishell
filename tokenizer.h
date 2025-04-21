/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:23:37 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/21 11:30:36 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "collector.h"
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
t_token				*ft_token_new(const char *value, size_t length);

void				ft_token_push(t_token **head, t_token *new_elem);
void				ft_token_addeoi(t_token **head, t_token *token);

int					is_unbalance(const char *str);
int					ft_str_isoperator(const char *str);
int					ft_char_isblank(char c);
int					ft_char_isnewline(char c);
int					ft_char_isoperator(char c);
int					ft_char_isdollar(char c);
int					ft_char_isquote(char c);
int					ft_char_iseoi(char c);

#endif
