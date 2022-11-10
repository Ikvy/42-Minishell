/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:25:35 by alevasse          #+#    #+#             */
/*   Updated: 2022/08/10 14:41:46 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_sep(char c, char sep)
{
	if (c == sep || c == '\0')
		return (1);
	return (0);
}

static size_t	ft_count_str(char const *s, char c)
{
	size_t	i;
	size_t	nb_str;

	i = 0;
	nb_str = 0;
	while (s[i])
	{
		if ((ft_check_sep(s[i], c) == 0)
			&& (ft_check_sep(s[i + 1], c) == 1))
			nb_str++;
		i++;
	}
	return (nb_str);
}

static int	ft_tab_split(char **split, char const *s, char c)
{
	size_t	start;
	size_t	end;
	size_t	index;

	index = 0;
	start = 0;
	while (s[start])
	{
		if (ft_check_sep(s[start], c) == 1)
			start++;
		else
		{
			end = 0;
			while (ft_check_sep(s[start + end], c) == 0)
				end++;
			split[index] = ft_substr(s, start, end);
			if (!split[index])
				return (ft_free_n_tab(split, index));
			start += end;
			index++;
		}
	}
	split[index] = 0;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	count_str;

	if (!s)
		return (NULL);
	count_str = ft_count_str(s, c);
	split = (char **)malloc(sizeof(char *) * (count_str + 1));
	if (!split)
		return (NULL);
	if (ft_tab_split(split, s, c) < 0)
		return (NULL);
	if (split[count_str] != 0)
		return (NULL);
	return (split);
}
