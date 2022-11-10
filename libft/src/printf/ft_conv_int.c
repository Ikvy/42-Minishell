/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:55:31 by alevasse          #+#    #+#             */
/*   Updated: 2022/04/21 09:15:28 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_prc_int(char *s, int len, int neg, t_opts opts)
{
	char	*new;

	if (neg)
		new = ft_strnew(opts.prc + 1);
	else
		new = ft_strnew(opts.prc);
	if (neg)
		s[0] = '0';
	if (opts.prc >= len)
	{
		ft_memset(new, '0', opts.prc);
		ft_strncpy(&new[opts.prc - len], s, len);
	}
	if (neg)
		new = ft_insert_str(new, "-", 0);
	if (opts.flags.plus && !neg)
		new = ft_insert_str(new, "+", 0);
	free(s);
	return (new);
}

static char	*ft_wdt_int(char *s, int len, int neg, t_opts opts)
{
	char	*new;

	new = ft_strnew(opts.wdt);
	ft_memset(new, ' ', opts.wdt);
	if (s[0] == '0' && s[1] == '\0' && opts.prc)
		s[0] = ' ';
	if (opts.flags.zero && !opts.flags.minus && !opts.prc && !opts.flags.dot)
	{
		ft_memset(new, '0', opts.wdt);
		if (opts.flags.plus)
			new[0] = '+';
	}
	if (opts.flags.minus)
		ft_strncpy(new, s, len);
	else if (opts.flags.minus && neg && opts.prc > len)
		ft_strncpy(&new[1], s, len);
	else
	{
		if (neg && opts.wdt > opts.prc && opts.prc)
			s[0] = '-';
		ft_strncpy(&new[opts.wdt - len], s, len);
	}
	free(s);
	return (new);
}

static char	*ft_neg_prc(char *s, int len, int neg, t_opts opts)
{
	char	*new;

	if (opts.wdt < opts.prc && opts.flags.zero)
		new = ft_strnew(opts.prc + 1);
	else
		new = ft_strdup(s);
	new[0] = '0';
	if (opts.prc > len)
		new = ft_prc_int(new, len, neg, opts);
	if (!opts.flags.zero && opts.wdt && !opts.prc)
	{
		new[0] = '-';
		new = ft_wdt_int(new, len, neg, opts);
	}
	else
	{
		len = ft_strlen_int(new);
		new = ft_wdt_int(new, len, neg, opts);
		if (opts.wdt > opts.prc && !opts.flags.minus && opts.flags.dot)
			new[0] = ' ';
		else
			new[0] = '-';
	}
	free(s);
	return (new);
}

static char	*ft_opts_int(char *s, int len, int neg, t_opts opts)
{
	char	*new;

	new = ft_strdup(s);
	if (opts.flags.plus && !opts.flags.zero && !opts.prc && !neg)
		ft_insert_str(new, "+", 0);
	if (opts.prc >= len)
		new = ft_prc_int(new, len, neg, opts);
	len = ft_strlen_int(new);
	if (neg && opts.wdt > len)
		new = ft_neg_prc(new, len, neg, opts);
	else if (opts.wdt > ft_strlen_int(new))
	{
		len = ft_strlen_int(new);
		new = ft_wdt_int(new, len, neg, opts);
	}
	if (opts.flags.space && !opts.flags.plus && !opts.prc && !neg)
		new = ft_insert_str(new, " ", 0);
	free(s);
	return (new);
}

int	ft_conv_int(int fd, int n, t_opts opts)
{
	char	*s;
	int		neg;
	int		len;

	neg = 0;
	if (n < 0)
		neg = 1;
	s = ft_itoa(n);
	if (n == 0 && opts.flags.dot && !opts.prc)
		s[0] = '\0';
	len = ft_strlen_int(s);
	s = ft_opts_int(s, len, neg, opts);
	len = ft_strlen_int(s);
	if (n == 0 && !opts.prc && opts.flags.dot && !opts.wdt)
	{
		s[0] = '\0';
		len = ft_strlen_int(s);
	}
	else
		len = ft_putstr_size_fd(s, fd);
	free(s);
	return (len);
}
