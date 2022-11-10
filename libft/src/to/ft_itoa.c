/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:43:06 by alevasse          #+#    #+#             */
/*   Updated: 2022/03/23 15:37:00 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_len(int n)
{
	size_t	count_len;

	count_len = 0;
	if (n == 0)
		count_len++;
	if (n < 0)
	{
		n = -n;
		count_len++;
	}
	while (n > 0)
	{
		n = n / 10;
		count_len++;
	}
	return (count_len);
}

char	*ft_itoa(int n)
{
	char	*dst;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_count_len(n);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	dst[len] = '\0';
	if (n == 0)
		dst[0] = '0';
	if (n < 0)
	{
		dst[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		dst[len - 1] = 48 + (n % 10);
		n = n / 10;
		len--;
	}
	return (dst);
}
