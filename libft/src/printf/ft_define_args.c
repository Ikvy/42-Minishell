/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 07:50:31 by alevasse          #+#    #+#             */
/*   Updated: 2022/04/21 09:15:49 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_define_args(int fd, const char *fmt, va_list args, int *i)
{
	t_opts	opts;

	opts = ft_get_opts(fmt, i);
	if (fmt[*i] == 'c')
		return (ft_conv_char(fd, va_arg(args, int), opts));
	else if (fmt[*i] == 's')
		return (ft_conv_str(fd, va_arg(args, char *), opts));
	else if (fmt[*i] == 'd' || fmt[*i] == 'i')
		return (ft_conv_int(fd, va_arg(args, int), opts));
	else if (fmt[*i] == 'u')
		return (ft_conv_uint(fd, va_arg(args, unsigned int), opts));
	else if (fmt[*i] == 'x')
		return (ft_conv_hex(fd, va_arg(args, unsigned int), opts, 0));
	else if (fmt[*i] == 'X')
		return (ft_conv_hex(fd, va_arg(args, unsigned int), opts, 1));
	else if (fmt[*i] == 'p')
		return (ft_conv_ptr(fd, va_arg(args, unsigned long), opts));
	else
		return (ft_conv_char(fd, fmt[*i], opts));
}
