/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 07:45:04 by alevasse          #+#    #+#             */
/*   Updated: 2022/04/21 09:14:49 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_int(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_putchar_size(char c)
{
	ft_putchar(c);
	return (1);
}

int	ft_putstr_size(const char *s)
{
	if (!s)
		return (0);
	ft_putstr(s);
	return (ft_strlen_int(s));
}

int	ft_putchar_size_fd(char c, int fd)
{
	ft_putchar_fd(c, fd);
	return (1);
}

int	ft_putstr_size_fd(char *s, int fd)
{
	if (!s)
		return (0);
	ft_putstr_fd(s, fd);
	return (ft_strlen_int(s));
}