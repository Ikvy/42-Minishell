/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:38:43 by alevasse          #+#    #+#             */
/*   Updated: 2022/05/16 13:53:01 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(unsigned int n, char *base)
{
	if ((int)n >= ft_strlen(base))
		ft_putnbr_base(n / ft_strlen(base), base);
	ft_putchar(base[n % ft_strlen(base)]);
}
