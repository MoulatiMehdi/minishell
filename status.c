/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:22:52 by mmoulati          #+#    #+#             */
/*   Updated: 2025/05/20 09:22:53 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "status.h"

unsigned char	*ft_status_ptr(void)
{
	static unsigned char	status;

	return (&status);
}

void	ft_status_exit(int status)
{
	ft_clear();
	exit(status);
}
