/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:36:00 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/16 18:36:00 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_signal_init(void)
{
	size_t		i;
	size_t		size;
	static int	sigs[] = {SIGHUP, SIGILL, SIGTRAP, SIGABRT, SIGFPE, SIGBUS,
		SIGSEGV, SIGSYS, SIGPIPE, SIGALRM, SIGXCPU, SIGXFSZ, SIGVTALRM,
		SIGUSR1, SIGUSR2, SIGINT, SIGQUIT, SIGTERM};

	i = 0;
	size = sizeof(sigs) / sizeof(sigs[0]);
	while (i < size)
	{
		signal(sigs[i], SIG_DFL);
		i++;
	}
	signal(SIGQUIT, ft_signal_quit);
}

volatile sig_atomic_t	*ft_sigint_recieved(void)
{
	static volatile sig_atomic_t	received = 0;

	return (&received);
}

void	ft_heredoc_sigint(int signal)
{
	(void)signal;
	*ft_sigint_recieved() = 1;
}
