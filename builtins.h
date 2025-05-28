/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:05:05 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/26 17:33:45 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"
# include "libft/libft.h"
# include "status.h"
# include "stdio.h"
# include "config.h"

int		echo_cmd(char **args);
int		pwd_cmd(char **args);
int		env_cmd(char **args);
int		exit_cmd(char **args);
int		export_cmd(char **args);
int		unset_cmd(char **args);
int		cd_cmd(char **args);
void	*ft_get_env(char *key, t_array *env);
char	*get_var_key(char *var);
char	*get_var_value(const char *var);
void	compute_limit(int sign, unsigned long *limit);
int		is_valid_var_name(char c);
int		is_valid_char(char c);
int		is_valid_identifier(const char *var);
int		print_export(t_array *env);
void	print_export_error(char *arg);

#endif