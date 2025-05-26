/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:06:52 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/26 17:34:07 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>
#include <unistd.h>

static int	is_all_ns(const char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	i = 2;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_flags(char *const args[], int *index)
{
	int	omit_nl;

	omit_nl = 1;
	*index = 0;
	while (args[*index] && is_all_ns(args[*index]))
	{
		omit_nl = 0;
		(*index)++;
	}
	return (omit_nl);
}

static int	print_arguments(char *const args[], int start)
{
	int	i;
	int	ret;

	i = start;
	while (args[i])
	{
		ret = ft_putstr_fd(args[i], 1);
		if (ret < 0)
		{
			perror(SHELL_NAME "echo: write error");
			return (1);
		}
		if (args[i + 1] && write(1, " ", 1) < 0)
		{
			perror(SHELL_NAME "echo: write error");
			return (1);
		}
		i++;
	}
	return (0);
}

int	echo_cmd(char **args)
{
	int	arg_idx;
	int	omit_nl;

	omit_nl = parse_flags(args, &arg_idx);
	if (print_arguments(args, arg_idx))
		return (1);
	if (omit_nl && write(1, "\n", 1) < 0)
	{
		perror(SHELL_NAME "echo: write error");
		return (1);
	}
	return (0);
}
