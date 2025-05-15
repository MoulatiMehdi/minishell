/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:50:37 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/15 14:11:08 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

static void	cleanup_and_exit(int code)
{
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", 1);
	/* TODO: free resources here */
	exit(code);
}

static void	numeric_error(char *arg)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	cleanup_and_exit(255);
}

static unsigned long	parse_digits(const char *arg, unsigned long idx,
		unsigned long limit)
{
	unsigned long	result;

	result = 0UL;
	while (arg[idx])
	{
		if (!ft_isdigit(arg[idx]))
			numeric_error((char *)arg);
		if (result > limit / 10UL || (result == limit / 10UL
				&& (unsigned long)(arg[idx] - '0') > limit % 10UL))
			numeric_error((char *)arg);
		result = result * 10UL + (unsigned long)(arg[idx] - '0');
		idx++;
	}
	return (result);
}

static long	parse_exit_code(char *arg)
{
	int				sign;
	unsigned long	idx;
	unsigned long	limit;
	unsigned long	value;

	if (!arg || *arg == '\0')
		numeric_error(arg);
	sign = 1;
	idx = 0;
	if (arg[idx] == '+' || arg[idx] == '-')
	{
		if (arg[idx] == '-')
			sign = -1;
		idx++;
	}
	compute_limit(sign, &limit);
	value = parse_digits(arg, idx, limit);
	return ((long)(value * (unsigned long)sign));
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
