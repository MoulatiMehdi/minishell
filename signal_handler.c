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

#include "execution.h"
#include "libft/libft.h"
#include "parser.h"
#include "status.h"

void	ft_signal_int(int signal)
{
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_redisplay();
	ft_status_set(128 + signal);
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
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal_int);
}

void	ft_signal_int_noninteractive(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 2);
	ft_status_exit(128 + signal);
}

void	ft_sigint_newline(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 2);
	ft_status_set(128 + signal);
}

void	ft_signal_noninteractive(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal_int_noninteractive);
}
