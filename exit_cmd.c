/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:50:37 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/12 15:00:33 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int is_numeric(const char *str)
{
    int i = 0;

    if (!str || !*str)
        return 0;
    if ((str[0] == '-' || str[0] == '+') && str[1] != '\0')
        i = 1;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

static void  print_exit_and_die(int code)
{
    ft_putendl_fd("exit", 1);
    exit(code);
}

int  exit_cmd(t_cmd *cmd, int last_return)
{
    long    status;
    char   *arg;

    if (!cmd)
        return (1);
    if (!cmd->args || !cmd->args[0])
        print_exit_and_die(last_return);
    arg = cmd->args[0];
    if (!is_numeric(arg))
    {
        ft_putstr_fd("exit: ", 2);
        ft_putstr_fd(arg, 2);
        ft_putendl_fd(": numeric argument required", 2);
        print_exit_and_die(255);
    }
    if (cmd->args[1])
    {
        ft_putendl_fd("exit: too many arguments", 2);
        return (1);
    }
	int code = ft_atoi(arg);
	status = code % 256;
	if (status < 0)
		status += 256;
	print_exit_and_die(status);
    return (0);
}
