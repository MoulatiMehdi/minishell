/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbge_collector.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoulati <mmoulati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:09:45 by mmoulati          #+#    #+#             */
/*   Updated: 2025/04/16 16:09:45 by mmoulati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBGE_COLLECTOR_H
# define GARBGE_COLLECTOR_H

# define GARBDE_COLLECTOR_H

# include <stdlib.h>

void	ft_free(void *addr);
void	*ft_malloc(size_t size);
int		ft_clear(void);

#endif // !GARBGE_COLLECTOR_H
