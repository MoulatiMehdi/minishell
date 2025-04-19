/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:09:45 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/17 10:43:30 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H

# define COLLECTOR_H

# include "libft.h"
# include <stdlib.h>

void	ft_free(void *addr);
void	*ft_malloc(size_t size);
int		ft_clear(void);

#endif // !GARBGE_COLLECTOR_H
