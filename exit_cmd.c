/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:50:37 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/14 16:53:14 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

static void	cleanup_and_exit(int code)
{
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 1);
	// TODO: free resources here
	exit(code);
}

static void	numeric_error(char *arg)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	cleanup_and_exit(255);
}

static long	parse_exit_code(char *arg)
{
	int				i;
	int				sign;
	unsigned long	result;
	unsigned long	limit;

	if (!arg || *arg == '\0')
		numeric_error(arg);
	i = 0;
	sign = 1;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			sign = -1;
		i++;
	}
	result = 0UL;
	if (sign == 1)
		limit = (unsigned long)LONG_MAX;
	else
		limit = (unsigned long)LONG_MAX + 1UL;

	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			numeric_error(arg);

		/* detect overflow before multiplying */
		if (result > limit / 10UL
		 || (result == limit / 10UL
		     && (unsigned long)(arg[i] - '0') > (limit % 10UL)))
			numeric_error(arg);

		result = result * 10UL + (unsigned long)(arg[i] - '0');
		i++;
	}
	return ((long)(result * (unsigned long)sign));
}


int	exit_cmd(t_cmd *cmd, int last_return)
{
	long	code;

	if (!cmd)
		return (1);
	if (!cmd->args || !cmd->args[0])
		cleanup_and_exit(last_return);
	code = parse_exit_code(cmd->args[0]);
	if (cmd->args[1])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	code %= 256;
	if (code < 0)
		code += 256;
	cleanup_and_exit((int)code);
	return (0);
}
