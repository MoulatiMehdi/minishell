/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:31:18 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/24 15:37:43 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "env.h"
# include "libft/libft.h"
# include "parser.h"
# include "tokenizer.h"
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>

# define IFS "\n\t "

void	expand_token(t_token *token);
void	join_quotes(t_word *head);
t_array	*field_splitting(t_word *word);
void	ft_pathname_expansion(t_token *token, t_array *fields);
void	expand_param(t_word *word);

DIR		*ft_diren_open(char *path);
char	*ft_diren_getname(DIR *stream);
t_list	*ft_pattern_matchall(char *word, char *mask, char *path[2]);
char	*get_env_value(const char *var_name, size_t len);
int		ft_path_iscurrentdir(char *prefix);
#endif
