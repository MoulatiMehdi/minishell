/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_init.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:13:22 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/26 13:13:24 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_INIT_H

# define TOKENIZER_INIT_H

# include "tokenizer.h"

t_token	*ft_token_new(const char *value, size_t length);

void	ft_token_push(t_token **head, t_token *new_elem);
void	ft_token_addeoi(t_token **head, t_token *token);

int		is_unbalance(const char *str);
int		ft_str_isoperator(const char *str);
int		ft_char_isblank(char c);
int		ft_char_isnewline(char c);
int		ft_char_isoperator(char c);
int		ft_char_isdollar(char c);
int		ft_char_isquote(char c);
int		ft_char_iseoi(char c);

#endif // !
