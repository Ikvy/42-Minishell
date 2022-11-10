/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:51:49 by alevasse          #+#    #+#             */
/*   Updated: 2022/04/21 09:15:21 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_hex(int upper)
{
	if (upper == 1)
		return ("0X");
	else
		return ("0x");
}

static char	*ft_prc_hex(char *s, int len, int upper, t_opts opts)
{
	char	*new;

	new = ft_strnew(opts.prc);
	ft_memset(new, '0', opts.prc);
	ft_strncpy(&new[opts.prc - len], s, len);
	if (opts.flags.sharp)
		new = ft_insert_str(new, ft_get_hex(upper), 0);
	free(s);
	return (new);
}

static char	*ft_wdt_hex(char *s, int len, t_opts opts)
{	
	char	*new;

	if (opts.flags.sharp && opts.flags.zero)
	{
		new = ft_strnew(opts.wdt);
		opts.wdt -= 2;
	}
	else
		new = ft_strnew(opts.wdt);
	ft_memset(new, ' ', opts.wdt);
	if (opts.flags.zero && !opts.flags.minus && !opts.flags.dot)
		ft_memset(new, '0', opts.wdt);
	if (opts.flags.minus)
		ft_strncpy(new, s, len);
	else
		ft_strncpy(&new[opts.wdt - len], s, len);
	free(s);
	return (new);
}

static char	*ft_opts_hex(char *s, int len, int upper, t_opts opts)
{
	char	*new;

	if (s[len - 1] == '0' && opts.flags.dot && !opts.prc && opts.wdt)
		ft_memset(s, ' ', len);
	if (!opts.prc && !opts.wdt && !opts.flags.zero && opts.flags.sharp
		&& !(s[0] == '0' && s[1] == '\0') && !opts.flags.dot)
		new = ft_strjoin(ft_get_hex(upper), s);
	else
		return (s);
	free(s);
	return (new);
}

int	ft_conv_hex(int fd, unsigned int n, t_opts opts, int upper)
{
	char	*s;
	int		len;

	s = ft_itoa_hex(n, upper);
	if (n == 0 && opts.flags.dot && !opts.prc)
		s[0] = '\0';
	len = ft_strlen_int(s);
	if (opts.prc > len)
		s = ft_prc_hex(s, len, upper, opts);
	len = ft_strlen_int(s);
	if (opts.wdt > len)
	{
		if (opts.flags.sharp && opts.wdt && !opts.flags.dot
			&& !opts.flags.zero)
				s = ft_insert_str(s, ft_get_hex(upper), 0);
		len = ft_strlen_int(s);
		s = ft_wdt_hex(s, len, opts);
		if (opts.flags.sharp && opts.flags.zero && !opts.flags.dot)
			s = ft_insert_str(s, ft_get_hex(upper), 0);
	}
	len = ft_strlen_int(s);
	s = ft_opts_hex(s, len, upper, opts);
	len = ft_putstr_size_fd(s, fd);
	free(s);
	return (len);
}
