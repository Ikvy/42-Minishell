/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:17:30 by alevasse          #+#    #+#             */
/*   Updated: 2022/05/19 11:01:18 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	size_t	src_len;
	size_t	dst_len;

	if (!dst)
		return (ft_strdup(src));
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	dst = (char *)ft_realloc(dst, src_len + dst_len + 1);
	ft_strcpy(dst + dst_len, src);
	return (dst);
}
