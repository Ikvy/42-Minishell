/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:56:06 by alevasse          #+#    #+#             */
/*   Updated: 2022/04/21 09:15:34 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_wdt_ptr(char *s, int len, t_opts opts)
{
	char	*new;

	new = ft_strnew(opts.wdt);
	ft_memset(new, ' ', opts.wdt);
	if (opts.flags.minus)
		ft_strncpy(new, s, len);
	else
		ft_strncpy(&new[opts.wdt - len], s, len);
	free(s);
	return (new);
}

int	ft_conv_ptr(int fd, unsigned long n, t_opts opts)
{
	char	*s;
	int		len;

	s = ft_itoa_ptr(n);
	s = ft_insert_str(s, "0x", 0);
	len = ft_strlen_int(s);
	if (opts.wdt > len)
		s = ft_wdt_ptr(s, len, opts);
	len = ft_strlen_int(s);
	ft_putstr_fd(s, fd);
	free(s);
	return (len);
}
