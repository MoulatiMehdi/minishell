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
#include <readline/readline.h>
#include <signal.h>

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
}

void	ft_signal_int(int signal)
{
	rl_replace_line("", 0);
	write(2, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal_bashignore(void)
{
	signal(SIGSTOP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal_int);
}

volatile sig_atomic_t	*ft_sigint_recieved(void)
{
	static volatile sig_atomic_t	received = 0;

	return (&received);
}

void	ft_heredoc_sigint(int signal)
{
	*ft_sigint_recieved() = 1;
}
