/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_subshell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okhourss <okhourss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:53:23 by okhourss          #+#    #+#             */
/*   Updated: 2025/05/26 14:55:04 by okhourss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "execution.h"
#include "expansion.h"
#include "libft/libft.h"
#include "parser.h"

void	ft_subshell_child(t_ast *ast, t_ast *child)
{
	ft_signal_child();
	ft_env_set(ft_copy_env(ft_env_get()));
	if (ft_redirect(ast->redirect))
		ft_status_exit(1);
	ft_status_exit(ft_execute_andor(child));
}
