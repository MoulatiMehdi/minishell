/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:36:00 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/26 17:44:24 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft.h"
#include "parser.h"

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

void	ft_signal_parent(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sigint_prompt);
}
