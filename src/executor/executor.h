#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../lexer/lexer.h"
# include "../parser/tree.h"

# define CHILD_PROCESS 0

typedef struct s_fd
{
    int fd[2];
    int fd_close;
    int first_in;
    int first_out;

}       t_fd;


////void    ft_exec(t_ast_node *exec, t_ctx *ctx);
//int     ft_exec_node(t_ast_node *node, t_ctx *ctx);
//int     ft_exec_cmd(t_ast_node *exec, t_ctx *ctx);
//int     ft_exec_redir(t_ast_node *exec, t_ctx *ctx);
//int     ft_exec_end_or(t_ast_node *exec, t_ctx *ctx);
//int     ft_exec_pipe(t_ast_node *exec, t_ctx *ctx);
int	    ft_strlen_tab(char **tab);
void    ft_init_fd_ctx(t_fd *fds);
void	ft_exec(t_ast_node *tree, t_ctx *ctx);
int		ft_exec_node(t_ast_node *node, t_ctx *ctx, t_fd *fds);
int		ft_exec_cmd(t_ast_node *node, t_ctx *ctx, t_fd *fds);
int     ft_exec_redir(t_ast_node *exec, t_ctx *ctx, t_fd *fds);
int		ft_exec_pipe(t_ast_node *node, t_ctx *ctx, t_fd *fds);

#endif
