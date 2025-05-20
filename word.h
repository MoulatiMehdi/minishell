/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:30:52 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/18 13:30:52 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_H
# define WORD_H

# include "libft/libft.h"
# include "tokenizer_init.h"

typedef enum e_word_type
{
	WORD_NONE,
	WORD_QUOTE_DOUBLE,
	WORD_QUOTE_SINGLE,
	WORD_WILDCARD
}					t_word_type;

typedef struct s_word
{
	t_word_type		type;
	const char		*value;
	size_t			length;
	struct s_word	*next;
}					t_word;

t_word				*ft_word_new(t_word_type type, const char *value,
						size_t length);
t_word				*ft_word_push(t_word **head, t_word_type type,
						const char *value, size_t length);
t_word				*ft_word_split(t_token *token);
char				*ft_word_join(t_word *word);
size_t				ft_word_none(t_word **head, t_token *token, size_t i);
size_t				ft_word_quote(t_word **head, t_token *token, size_t i);
size_t				ft_word_wildcard(t_word **head, t_token *token, size_t i);

#endif
