/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:53:49 by alevasse          #+#    #+#             */
/*   Updated: 2022/04/21 09:15:12 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_flag(char c)
{
	if (c == '+' || c == '-' || c == '0' || c == ' ' || c == '#')
		return (1);
	return (0);
}

void	ft_add_flags(t_flags *flags, char c)
{
	if (c == '+')
		flags->plus = 1;
	else if (c == '-')
		flags->minus = 1;
	else if (c == '0')
		flags->zero = 1;
	else if (c == ' ')
		flags->space = 1;
	else if (c == '#')
		flags->sharp = 1;
}
