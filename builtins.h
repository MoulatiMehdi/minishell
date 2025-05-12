/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:05:05 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/12 17:45:49 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "libft/libft.h"
#include "string.h"
#include "stdio.h"
typedef struct s_cmd
{
	char	*name;
	char **args;
}	t_cmd;

int echo_cmd(t_cmd *cmd);
int pwd_cmd(t_cmd *cmd);
int env_cmd(t_cmd *cmd);
int exit_cmd(t_cmd *cmd, int last_return);
int cd_cmd(t_cmd *cmd);

#endif