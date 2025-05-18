/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:55:36 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/18 14:55:37 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_signal_int(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	write(2, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal_quit(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	ft_putstr_fd("Quit (core dumped)\n", 2);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal_bashignore(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal_int);
}
