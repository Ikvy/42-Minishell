/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:14:15 by mmidon            #+#    #+#             */
/*   Updated: 2022/11/03 08:19:06 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOSE_H
# define CLOSE_H

#include "lexer/lexer.h"

void	ft_free_struct(t_ctx *ctx);
int		ft_return_err(char *arg, char *msg);
void	ft_sig_handler(int sig);
void    ft_free_tree(t_ast_node *tree);
void	ft_free_all(t_token *lexer);

#endif
