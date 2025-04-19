/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:23:37 by okhourss          #+#    #+#             */
/*   Updated: 2025/04/19 15:56:58 by mmoulati         ###   ########.fr       */
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
	TOKEN_OPERATOR,
	TOKEN_QUOTED_STRING,
	TOKEN_EOI
}					t_token_type;

typedef struct s_token
{
	const char		*value;
	t_token_type	type;
	size_t			length;
	struct s_token	*next;
}					t_token;

typedef enum e_state
{
	STATE_NONE,
	STATE_WORD,
	STATE_OPERATOR
}					t_state;

typedef struct s_tokenizer
{
	const char		*line;
	int				i;
	int				start;
	t_state			state;
	t_token			*head;
	t_token			*last;
}					t_tokenizer;

t_token				*tokenize(const char *line);
int					ft_str_isoperator(const char *str);

int					is_unbalance(const char *str);

t_token				*ft_token_new(const char *value, size_t length);
void				ft_token_push(t_token **head, t_token *new_elem);
void				ft_token_addeoi(t_token **head, t_token *token);

int					ft_char_isblank(char c);
int					ft_char_isnewline(char c);
int					ft_char_isoperator(char c);
int					ft_char_isdollar(char c);
int					ft_char_isquote(char c);
int					ft_char_iseoi(char c);
#endif
