/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:06:52 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/14 15:04:01 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int is_all_ns(const char *s)
{
    int i;

    if (!s || s[0] != '-' || s[1] != 'n')
        return (0);
    for (i = 2; s[i]; i++)
        if (s[i] != 'n')
            return (0);
    return (1);
}


int echo_cmd(t_cmd *cmd)
{
    int arg_idx = 0;
    int print_idx;
    int omit_nl  = 1;

    if (!cmd)
        return (1);
    while (cmd->args[arg_idx] && is_all_ns(cmd->args[arg_idx]))
    {
        omit_nl = 0;
        arg_idx++;
    }
	print_idx = arg_idx; 
    while (cmd->args[print_idx])
    {
        ft_putstr_fd(cmd->args[print_idx], 1);
        if (cmd->args[print_idx + 1])
            write(1, " ", 1);
		print_idx++;
    }
    if (omit_nl)
        write(1, "\n", 1);
    return (0);
}
