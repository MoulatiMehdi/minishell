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
	size_t				i;
	size_t				size;
	struct sigaction	act;
	static int			sigs[] = {SIGHUP, SIGILL, SIGTRAP, SIGABRT, SIGFPE,
					SIGBUS, SIGSEGV, SIGSYS, SIGPIPE, SIGALRM, SIGXCPU, SIGXFSZ,
					SIGVTALRM, SIGUSR1, SIGUSR2, SIGINT, SIGQUIT, SIGTERM};

	i = 0;
	size = sizeof(sigs) / sizeof(sigs[0]);
	act.sa_handler = SIG_DFL;
	sigemptyset(&act.sa_mask);
	act.sa_restorer = NULL;
	act.sa_flags = 0;
	while (i < size)
	{
		sigaction(sigs[i], &act, NULL);
		i++;
	}
	act.sa_flags = SA_RESTART;
	sigaction(SIGCHLD, &act, NULL);
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
	struct sigaction	act;

	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_restorer = NULL;
	act.sa_flags = 0;
	sigaction(SIGTSTP, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	signal(SIGINT, ft_signal_int);
}
