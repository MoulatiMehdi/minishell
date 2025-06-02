/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:55:36 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/25 17:22:37 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "status.h"

volatile sig_atomic_t	*ft_sigint_recieved(void)
{
	static volatile sig_atomic_t	received = 0;

	return (&received);
}

void	ft_sigint_clear(int signal)
{
	ft_status_exit(signal + 128);
	return ;
}

void	ft_sigint_heredoc(int signal)
{
	(void)signal;
	*ft_sigint_recieved() = 1;
}

void	ft_sigint_prompt(int signal)
{
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_redisplay();
	ft_status_set(128 + signal);
}
