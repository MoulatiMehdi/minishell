/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:09:35 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/27 09:28:48 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "execution.h"
#include "status.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	ft_env_init(envp);
	if (ft_shell_isinteractive())
		ft_shell_interactive();
	else
		ft_shell_noninteractive();
	return (ft_status_get());
}
