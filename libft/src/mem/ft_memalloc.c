/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:18:14 by alevasse          #+#    #+#             */
/*   Updated: 2022/04/11 10:36:52 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem_zone;

	mem_zone = (void *)malloc(size);
	if (!mem_zone)
		return (NULL);
	ft_bzero(mem_zone, size);
	return (mem_zone);
}
