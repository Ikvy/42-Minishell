#include <stdio.h>
#include "libft.h"
#include "parse_node.h"
#include "parse_utils.h"
#include "../lexer/lexer.h"
#include "tree.h"

int	ast_peek(t_token **lexer, int *tok, int size, int opts)
{
	int		i;
	t_token	*next;

	i = -1;
	next = *lexer;
	next = next->next;
	while (++i < size)
	{
		if ((int)next->type == tok[i])
		{
			if (opts && (int)next->type != TOK_EOF)
				*lexer = next;
			return (1);
		}
	}
	return (0);
}

void	ast_scanner_next(t_token **lexer)
{
	t_token	*next;

	next = *lexer;
	next = next->next;
	*lexer = next;
}

t_ast_node	*ast_cmd_node()
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(*node));
	node->node_type = NODE_CMD;
	return (node);
}

t_ast_node	*ast_redir_node(t_ast_node *cmd, char *file, int mode, int fd)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(*node));
	node->node_type = NODE_REDIR;
	node->data.redir.cmd = cmd;
	node->data.redir.file = file;
	node->data.redir.mode = mode;
	node->data.redir.fd = fd;
	return (node);
}

t_ast_node	*ast_pair_node
    (t_ast_node *left, t_ast_node *right, int node_type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(*node));
	node->node_type = node_type;
	node->data.pair.left = left;
	node->data.pair.right = right;
	return (node);	
}
