/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmidon <mmidon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:18:13 by mmidon            #+#    #+#             */
/*   Updated: 2022/09/22 10:05:20 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

t_token	*ft_lst_new_token(void)
{
	t_token	*new;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = NULL;
	new->string = 0;
	new->next = NULL;
	return (new);
}

t_token	*ft_token_last(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_token_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (*lst != NULL)
	{
		last = *lst;
		last = ft_token_last(*lst);
		last->next = new;
		return ;
	}
	*lst = new;
}
