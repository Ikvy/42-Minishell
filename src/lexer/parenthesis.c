#include <stdio.h>

#include "libft.h"
#include "lexer.h"

t_token	*ft_find_peer(t_token *l_parenthesis)
{
	int	i;

	i = 1;
	while (l_parenthesis->next && i != 0)
	{
		l_parenthesis = l_parenthesis->next;
		if (l_parenthesis->type == TOK_L_PARENTHESIS)
			i++;
		else if (l_parenthesis->type == TOK_R_PARENTHESIS)
			i--;
	}
	return (l_parenthesis);
}

static int	ft_parse_duplicate(t_token *lexer)
{
	t_token	*ptr;
	t_token	*tmp1;

	ptr = lexer;
	while (ptr && ptr->next)
	{
		if (ptr->type == TOK_L_PARENTHESIS && ptr->next->type == ptr->type)
		{
			tmp1 = ft_find_peer(ptr->next);
			if (tmp1->next->type == TOK_R_PARENTHESIS)
				return (-1);
		}
		ptr = ptr->next;
	}
	return (0);
}

int	ft_parse_parenth(t_token *lexer)
{
	int		count_parenth1;
	int		count_parenth2;
	t_token	*ptr;

	ptr = lexer;
	count_parenth1 = 0;
	count_parenth2 = 0;
	while (ptr)
	{
		if (ptr->type == TOK_L_PARENTHESIS)
			count_parenth1++;
		else if (ptr->type == TOK_R_PARENTHESIS)
			count_parenth2++;
		ptr = ptr->next;
	}
	if (count_parenth1 != count_parenth2 || ft_parse_duplicate(lexer) < 0)
		return (-1);
	return (0);
}
