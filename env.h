/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:24:26 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/26 14:58:55 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft/libft.h"

t_array	*ft_env_get(void);
t_array	*ft_env_set(t_array *new_env);
t_array *ft_init_env(char **env);
t_array *ft_copy_env(t_array *env);

#endif