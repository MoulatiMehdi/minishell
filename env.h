/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:24:26 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/28 10:45:58 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft/libft.h"
# include "status.h"

t_array	**ft_env_ptr(void);

t_array	*ft_env_get(void);
t_array	*ft_env_init(char **env);

char	*ft_env_set(char *key, char *value);
char	*ft_env_getvalue(char *key);
char	*ft_env_getvaluebysubstr(char *key, size_t length);

char	**ft_env_strs(void);

void	ft_env_clear(void);

// utils

void	ft_add_env_fundamentals(int shlvl, int oldpwd, int pwd);
void	ft_check_env_fundamentals(t_array **env);

int		ft_keycmp(char *key, char *key_env);

#endif
