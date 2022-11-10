/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 06:42:58 by alevasse          #+#    #+#             */
/*   Updated: 2022/05/19 06:42:59 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	size_t	cur_size;
	char	*new_ptr;

	if (!ptr)
		return (malloc(size));
	cur_size = sizeof(ptr);
	if (size <= cur_size)
		return (ptr);
	new_ptr = malloc(size);
	ft_memcpy(ptr, new_ptr, cur_size);
	free(ptr);
	return (new_ptr);
}
