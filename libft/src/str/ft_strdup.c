/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:25:45 by alevasse          #+#    #+#             */
/*   Updated: 2022/09/27 09:35:17 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;

	dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dst)
			return (NULL);
	if (s1)
		ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
	return (dst);
}
