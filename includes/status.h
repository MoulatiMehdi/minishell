/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:23:20 by mmoulati          #+#    #+#             */
/*   Updated: 2025/06/13 18:00:31 by vboxuser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_H

# define STATUS_H

# include "libft.h"

void			ft_status_exit(int status);
unsigned char	ft_status_set(unsigned char status);
unsigned char	ft_status_get(void);

#endif
