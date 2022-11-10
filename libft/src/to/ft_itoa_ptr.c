/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:02:48 by alevasse          #+#    #+#             */
/*   Updated: 2022/04/21 09:13:48 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_len(unsigned long n)
{
	size_t	count_len;

	count_len = 0;
	if (n == 0)
		count_len++;
	while (n > 0)
	{
		n /= 16;
		count_len++;
	}
	return (count_len);
}

char	*ft_itoa_ptr(unsigned long n)
{
	char	*index;
	char	*dst;
	size_t	len;

	index = "0123456789abcdef";
	len = ft_count_len(n);
	dst = (char *)malloc(sizeof(char) * (2 + len + 1));
	if (!dst)
		return (NULL);
	dst[len] = '\0';
	if (n == 0)
		dst[0] = '0';
	while (n > 0)
	{
		dst[len - 1] = index[n % 16];
		n /= 16;
		len--;
	}
	return (dst);
}
