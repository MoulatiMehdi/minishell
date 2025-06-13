/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:05:05 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/28 12:38:52 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "config.h"
# include "env.h"
# include "libft.h"
# include "status.h"
# include <stdio.h>

int		echo_cmd(char **args);
int		pwd_cmd(char **args);
int		env_cmd(char **args);
int		exit_cmd(char **args, int fd[2]);
int		export_cmd(char **args);
int		unset_cmd(char **args);
int		cd_cmd(char **args);

char	*get_var_value(const char *var);
char	*get_var_key(char *var);
void	compute_limit(int sign, unsigned long *limit);

int		print_export(t_array *env);
void	print_export_error(char *arg);

#endif
