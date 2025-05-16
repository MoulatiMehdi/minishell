/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:05:05 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/16 10:21:56 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft/libft.h"
# include "stdio.h"
# include "string.h"

typedef struct s_cmd
{
	char	*name;
	char	**args;
	t_array	*env;
}			t_cmd;

int			echo_cmd(t_cmd *cmd);
int			pwd_cmd(t_cmd *cmd);
int			env_cmd(t_cmd *cmd);
int			exit_cmd(t_cmd *cmd, int last_return);
int			export_cmd(t_cmd *cmd);
int			unset_cmd(t_cmd *cmd);
int			cd_cmd(t_cmd *cmd);
void		*ft_get_env(char *key, t_array *env);
char		*get_var_key(char *var);
char		*get_var_value(const char *var);
void		compute_limit(int sign, unsigned long *limit);
int			is_valid_var_name(char c);
int			is_valid_char(char c);
int			is_valid_identifier(const char *var);
int			print_export(t_array *env);
void		print_export_error(char *arg);

#endif