/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:23:52 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/07 08:03:04 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <termios.h>

#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "parser/parse.h"
#include "parser/tree.h"
#include "close.h"
#include "libft.h"
#include "lexer/lexer.h"
#include "builtins/builtin.h" 
#include "executor/executor.h"

t_prompt	g_prompt;
void	rl_replace_line(const char *text, int clear_undo);

char	**ft_dup(char	**envp)
{
	char	**dup;
	int	i = 0;

	while (envp[i++]);
	dup = malloc(sizeof(char *) * (i + i));
	i = -1;
	while (envp[++i])
		dup[i] = ft_strdup(envp[i]);
	dup[i] = 0;
	return (dup);
}

void	ft_init_sig(struct termios *term, struct termios *sign)
{
	struct sigaction	sa;

	g_prompt.prompt = 1;
	sa.sa_handler = ft_sig_handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_return_err("sigaction", strerror(errno));
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		ft_return_err("sigaction", strerror(errno));
	tcgetattr(STDIN_FILENO, sign);
	sign->c_lflag |= ECHOCTL;
	*term = *sign;
	term->c_lflag &= ~ECHOCTL;
}


t_ctx	*ft_init(char **envp)
{
	t_ctx				*ret;

	ret = malloc(sizeof(t_ctx));
	ret->start_lexer = NULL;
	ret->exec_tree = NULL;
	ret->env = ft_dup(envp);
	ret->fd_here_doc = NULL;
	ret->len = 0;
	ret->is_first = 1;
	return (ret);
}

void	ft_add_history(char *line)
{
	int	i;

	i = -1;
	while (line[++i] && ft_isspace(line[i]))
		if (line[i + 1] == '\0')
			return ;
	add_history(line);
}

void	ft_show_list(t_token *list)
{
	while (list)
	{
		printf("%s$\n", list->content);
		printf("%u$\n", list->type);
		list = list->next;
	}
}

void    ft_visit(t_ast_node *tree)
{
	int	i;

    if (tree->node_type == NODE_AND)
    {
        printf("Pair AND(\n");
		printf("left -->	"); 
        ft_visit(tree->data.pair.left);
		printf("right -->	"); 
        ft_visit(tree->data.pair.right);
        printf(")\n");
    }
	else if (tree->node_type == NODE_OR)
	{
	    printf("Pair OR(\n");
		printf("left -->	"); 
        ft_visit(tree->data.pair.left);
		printf("right -->	"); 
        ft_visit(tree->data.pair.right);
        printf(")\n");
    }
	else if (tree->node_type == NODE_PIPE)
	{
	    printf("Pair PIPE(\n");
		printf("left -->	"); 
        ft_visit(tree->data.pair.left);
		printf("right -->	"); 
        ft_visit(tree->data.pair.right);
        printf(")\n");
    }
	else if (tree->node_type == NODE_REDIR)
	{
		printf("Redir -->	(\"%s\")\n", tree->data.redir.file);
		if (tree->data.redir.cmd)
			ft_visit(tree->data.redir.cmd);
	}
    else if (tree->node_type == NODE_CMD)
	{
		i = -1;
		while (tree->data.cmd.tok_list[++i])
//			if (tree->data.cmd.tok_list != 0)
        	printf("Word -->	(\"%s\")\n", tree->data.cmd.tok_list[i]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx			*ctx;
	struct termios	term;
	struct termios	sign;
	char			*line_read;

	(void)(argc + argv);
	ft_init_sig(&term, &sign);
	ctx = ft_init(envp);
	while (1)
	{
		g_prompt.prompt = 1;
		dprintf(2, "prompt : \n");
		line_read = readline("minishell$ ");
		if (!line_read)
			return (0);
		if (line_read && *line_read)
		{

			ft_add_history(line_read);
			tcsetattr(STDIN_FILENO, TCSANOW, &sign);
			if (ft_lexer(ctx, line_read) < 0)
				printf("syntaxe error\n");
			else
			{
					
					ctx->exec_tree = ast_parse(ctx->start_lexer);
					ft_exec(ctx->exec_tree, ctx);
					if (ctx->exec_tree)
						ft_free_tree(ctx->exec_tree);
			}
			ft_free_all(ctx->start_lexer);
			ctx->start_lexer = NULL;
			tcsetattr(STDIN_FILENO, TCSANOW, &term);
		}
		free(line_read);
//		system("leaks minishell");
	}
	ft_free_struct(ctx);
	return (0);
}
