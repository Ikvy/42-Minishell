/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:02:57 by alevasse          #+#    #+#             */
/*   Updated: 2022/04/11 11:03:01 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_len(unsigned int n)
{
	size_t	count_len;

	count_len = 0;
	if (n == 0)
		count_len++;
	while (n > 0)
	{
		n /= 10;
		count_len++;
	}
	return (count_len);
}

char	*ft_itoa_unsigned(unsigned int n)
{
	char	*dst;
	size_t	len;

	len = ft_count_len(n);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	dst[len] = '\0';
	if (n == 0)
		dst[0] = '0';
	while (n > 0)
	{
		dst[len - 1] = 48 + (n % 10);
		n /= 10;
		len--;
	}
	return (dst);
}
