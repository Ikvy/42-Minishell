/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:03:39 by mmidon            #+#    #+#             */
/*   Updated: 2022/11/04 10:57:57 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>

# include "../parser/tree.h"

typedef struct g_prompt
{
	int	prompt;
	int ex_status;
}	t_prompt;

typedef enum e_token_type
{
	TOK_REDIR = 1,
	TOK_STRING,
	TOK_AND,
	TOK_OR,
	TOK_PIPE,
	TOK_L_PARENTHESIS,
	TOK_R_PARENTHESIS,
	TOK_ADD,
	TOK_START,
	TOK_EOF
}	t_token_type;

typedef enum e_string_type
{
	STRING_UNQUOTED = 1,
	STRING_QUOTED,
	STRING_DQUOTED
} t_string_type;

typedef enum e_redir_type
{
	REDIR_INFILE = 1,
	REDIR_OUTFILE,
	REDIR_HERE_DOC,
	REDIR_APP_OUTFILE
} t_redir_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	t_string_type	string;
	t_redir_type	redir;
	struct s_token	*next;
}					t_token;

typedef struct s_ctx
{
	t_token		*start_lexer;
	t_ast_node	*exec_tree;
	char		**env;
	char		**fd_here_doc;
	int			len;
	int			is_first;
}				t_ctx;

int		ft_parse_quotes(char *str);
char	*ft_chr_token(t_ctx *ctx, char *str);
int		ft_lexer(t_ctx *ctx, char *line);
int		ft_count_quotes(char *str);

#endif