/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmidon <mmidon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:05:32 by mmidon            #+#    #+#             */
/*   Updated: 2022/09/22 10:13:20 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"
#include "lexer_utils.h"
#include "../close.h"
#include "token_list.h"
#include "parenthesis.h"

void	ft_show_list(t_token *list);

int	ft_count_quotes(char *str)
{
	int	state;
	int	count_squotes;
	int	count_dquotes;
	int	i;

	i = -1;
	state = 0;
	count_dquotes = 0;
	count_squotes = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && state != 2)
		{
			count_squotes++;
			if (count_squotes % 2 != 0)
				state = 1;
			else
				state = 0;
		}
		else if (str[i] == '"' && state != 1)
		{
			count_dquotes++;
			if (count_dquotes % 2 != 0)
				state = 2;
			else
				state = 0;
		}
	}
//	if (count_dquotes % 2 || count_squotes % 2)
//		return (i);
	return (count_squotes);
}

int	ft_parse_quotes(char *str)
{
	int	i;

	i = ft_count_quotes(str);
	if (i % 2)
		printf("error: unclosed quote\n");
	return (i);
}

char	*ft_chr_token(t_ctx *ctx, char *str)
{
	t_token	*token;

	token = ft_lst_new_token();
	if (str[0] == '<' || str[0] == '>')
		str = ft_add_two_char(str, token);
	else if (str[0] == '&' && str[1] == '&')
		str = ft_add_two_char(str, token);
	else if (str[0] == '|')
		str = ft_add_two_char(str, token);
	else if (str[0] == '(' || str[0] == ')')
		str = ft_add_caractere(str, token);
	else
		str = ft_add_string(str, token);
	ft_token_add_back(&ctx->start_lexer, token);
	return (str);
}

int	ft_lexer(t_ctx *ctx, char *line)
{
	char	*tmp;
	t_token	*token;

	tmp = line;
	token = ft_lst_new_token();
	token->type = TOK_START;
	ft_token_add_back(&ctx->start_lexer, token);
	token = ft_lst_new_token();
	token->type = TOK_EOF;
	while (*tmp)
	{
		if (ft_isspace(*tmp))
			tmp++;
		else
			tmp = ft_chr_token(ctx, tmp);
	}
	ft_token_add_back(&ctx->start_lexer, token);
	return (ft_parse_parenth(ctx->start_lexer));
}
