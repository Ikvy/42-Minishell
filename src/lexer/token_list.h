/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmidon <mmidon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:17:12 by mmidon            #+#    #+#             */
/*   Updated: 2022/09/22 10:25:13 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

t_token	*ft_lst_new_token(void);
t_token	*ft_token_last(t_token *lst);
void	ft_token_add_back(t_token **lst, t_token *new);

#endif
