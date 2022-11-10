/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:16:09 by alevasse          #+#    #+#             */
/*   Updated: 2022/04/21 10:10:21 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_gnl(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	len_s;
	size_t	i;

	if (!s)
		return (NULL);
	len_s = 0;
	while (s[len_s] && len_s < start + len)
		len_s++;
	if (len < start)
		return (NULL);
	len_s = len_s - start;
	new = malloc(sizeof(char *) * (len_s + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i <= len_s)
	{
		new[i] = s[i + start];
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	ft_add_buff(char **ret, char *buff)
{
	char	*new;
	int		i;
	int		j;

	if (!*ret)
		*ret = ft_substr_gnl("", 0, 0);
	new = malloc(sizeof(char) * (ft_strlen(*ret) + ft_strlen(buff) + 1));
	i = 0;
	while ((*ret)[i])
	{
		new[i] = (*ret)[i];
		i++;
	}
	j = 0;
	while (buff[j])
	{
		new[i] = buff[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(*ret);
	*ret = new;
}

char	*ft_get_line(char **ret)
{
	char	*new;
	char	*line;
	int		pos;

	if (!*ret)
		return (NULL);
	pos = ft_strchr_gnl(*ret, '\n');
	if (pos == -1)
		pos = ft_strlen(*ret) - 1;
	line = ft_substr_gnl(*ret, 0, pos);
	new = ft_substr_gnl(*ret, pos + 1, ft_strlen(*ret) - 1);
	free(*ret);
	*ret = new;
	return (line);
}
