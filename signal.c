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

#include "execution.h"
#include "libft/libft.h"
#include "parser.h"
#include "status.h"
#include <signal.h>

volatile sig_atomic_t	*ft_sigint_recieved(void)
{
	static volatile sig_atomic_t	received = 0;

	return (&received);
}

void	ft_signal_child(void)
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
}

void	ft_heredoc_sigint(int signal)
{
	(void)signal;
	*ft_sigint_recieved() = 1;
}

void	ft_signal_int(int signal)
{
	rl_replace_line("", 0);
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_redisplay();
	ft_status_set(128 + signal);
}

void	ft_signal_parent(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal_int);
}
