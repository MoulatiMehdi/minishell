/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:24:26 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/27 07:45:43 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft/libft.h"

t_array	**ft_env_ptr(void);

t_array	*ft_env_get(void);
t_array	*ft_env_init(char **env);

char	*ft_env_set(char *key, char *value);
char	*ft_env_getvalue(char *key);
char	*ft_env_getvaluebysubstr(char *key, size_t length);

char	**ft_env_strs(void);

void	ft_env_clear(void);
#endif
