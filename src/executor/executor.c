#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include "libft.h"
#include "executor.h"
#include "../lexer/lexer.h"
#include "../parser/parse.h"
#include "../parser/tree.h"
#include "path.h"
#include "../close.h"

t_prompt	g_prompt;

/*void    ft_get_heredoc(char *eof)
{
    char    *line;
    char    *limiter;
    int     fd;

    fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return ;
    line = "";
    limiter = eof;
    while (1)
    {
        ft_putstr_fd("> ", 1);
        line = get_next_line(STDIN_FILENO);
        if (line == NULL)
            break ;
        if (ft_strlen(limiter) + 1 == ft_strlen(line)
            && !ft_strncmp(line, limiter, ft_strlen(limiter)))
            break ;
        else
            ft_putstr_fd(line, fd);
        free(line);
    }
}

void    ft_exec_redir(char **redir)
{
    int i;
    int fd;

    i = -1;
    while (redir[++i])
    {
        if (redir[i][0] == '0')
        {
            fd = open(redir[i] + 1, O_RDONLY);
            if (fd == -1)
                return ;
       }
        else if (redir[i][0] == '1')
        {
            fd = open(redir[i] + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
                return ;
        }
        else if (redir[i][0] == '2')
        {
            fd = open(redir[i] + 1, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
                return ;
        }
        else if (redir[i][0] == '3')
        {
            ft_get_heredoc(redir[i] + 1);
            fd = open(".here_doc", O_RDONLY);
            if (fd == -1)
                return ;
            unlink(".here_doc");
        }
        if (redir[i][0] != '0')
            dup2(fd, 1);
        else if (redir[i][0] == '0')
            dup2(fd, 0);
        close(fd);
    }
}

void	ft_open_pipes(t_ast_node *exec)
{
    int fd[2];

	if (pipe(fd) == -1)
		return ;
	exec->data.content.next->data.content.pipes[1] = fd[1];
	exec->data.content.pipes[0] = fd[0];
}

void    ft_dup_pipe(t_ast_node *exec)
{
    if (exec->data.content.pipes[1])
        dup2(exec->data.content.pipes[1], STDOUT_FILENO);
    if (exec->data.content.pipes[0])
        dup2(exec->data.content.pipes[0], STDIN_FILENO);
}

void    ft_execve(t_ast_node *exec, t_ctx *ctx)
{
    char *cmd_path;

    cmd_path = ft_chr_path(exec->data.content.tok_list[0], ctx->env);
    if (!cmd_path)
        return ;
    execve(cmd_path, exec->data.content.tok_list ,ctx->env);
    exit(1);
}

void ft_fork(t_ast_node *exec, t_ctx *ctx)
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
        return ;
    if (pid == 0)
    {
        if (exec->data.content.tok_list[0] == 0)
            return ;
        if (exec->data.content.pipes[0] || exec->data.content.pipes[1])
            ft_dup_pipe(exec);
        if (exec->data.content.redirect && exec->data.content.redirect[0] != NULL)
            ft_exec_redir(exec->data.content.redirect);
        ft_execve(exec, ctx);
   }
 //   return (pid);
}

void    ft_wait(pid_t l_pid, t_ctx *ctx)
{
    int     status;
    pid_t   pid;

    while (1)
    {
        pid = wait(&status);
        if (pid == l_pid)
            ctx->ex_status = WEXITSTATUS(status);
        if (pid < 0 && errno != EINTR)
            break ;
    }
}


int    ft_exec_cmd(t_ast_node *exec, t_ctx *ctx)
{
    int pid;
    int status;
    int ret;

    status = 0;
    if (!exec)
        return (-1);
    if (exec->node_type == NODE_PIPE || exec->node_type == NODE_DATA)
    {
        if (exec->data.content.next)
        {
            ft_open_pipes(exec);
            ft_exec_cmd(exec->data.content.next, ctx);
        }
        ft_fork(exec, ctx);
        if (exec->data.content.pipes[0] > 0)
            close(exec->data.content.pipes[0]);
        if (exec->data.content.pipes[1] > 0)
            close(exec->data.content.pipes[1]);
    }
    else if (exec->node_type == NODE_AND || exec->node_type == NODE_OR)
    {
        if (fork() == 0)
            ft_exec_cmd(exec->data.pair.left, ctx);
        wait(0);
        ft_exec_cmd(exec->data.pair.right, ctx);
    }
    pid = wait(&status);
    if (WIFEXITED(status))
    {
		ret = WEXITSTATUS(status);
        return (ret);
    }
    return (0);
}
*/

/*void    ft_exec(t_ast_node *exec, t_ctx *ctx)
{
    int	    i;
	int	    children;
	
	if (!exec)
		exit(1);
	i = -1;
	children = ft_exec_node(exec, ctx);
    printf("children egale %d\n", children);
    printf("i egal %d\n", i);
	while (++i < children)
		wait(0);
}

int ft_exec_node(t_ast_node *node, t_ctx *ctx)
{
	static int children;
    if (!node)
        exit(1);
    if (node->node_type == NODE_CMD)
        return (ft_exec_cmd(node, ctx));
    else if (node->node_type == NODE_REDIR)
        return (ft_exec_redir(node, ctx));
    else if (node->node_type == NODE_AND || node->node_type == NODE_OR)
        return (ft_exec_end_or(node, ctx));
    else if (node->node_type == NODE_PIPE)
        return (ft_exec_pipe(node, ctx));
    else
        return (0);
}

int    ft_exec_cmd(t_ast_node *exec, t_ctx *ctx)
{
    char    *cmd_path;

    if (fork() == 0)
    {
        dup2(pipes[1], STDOUT_FILENO);
        if (exec->data.cmd.tok_list[0] == 0)
            exit(1);
        cmd_path = ft_chr_path(exec->data.cmd.tok_list[0], ctx->env);
        if (!cmd_path)
            exit(1);
        execve(cmd_path, exec->data.cmd.tok_list, ctx->env);
        ft_fprintf(2, "exec %s failed\n", exec->data.cmd.tok_list[0]);
    }
    return (1);
}

int    ft_exec_redir(t_ast_node *exec, t_ctx *ctx)
{
    close(exec->data.redir.fd);
    close(pipes[0])
    close(pipes[1]);
    if (open(exec->data.redir.file, exec->data.redir.mode, 0664) == -1)
    {
        ft_fprintf(2, "open %s failed\n", exec->data.redir.file);
        exit(1);
    }
    ft_exec_node(exec->data.redir.cmd, ctx);
    return (0);
}

int    ft_exec_end_or(t_ast_node *exec, t_ctx *ctx)
{
    pid_t   pid;
    int     status;
    int     children;

    children = 0;
    pid = fork();
    if (pid == 0)
        children += ft_exec_node(exec->data.pair.left, ctx);
    waitpid(pid, &status, 0);
    if (status == 2)
        status += 128;
    else
        status = WEXITSTATUS(status);
    if (exec->node_type == NODE_AND && status)
        children += ft_exec_node(exec->data.pair.left, ctx);
    return (children);
}

int    ft_exec_pipe(t_ast_node *exec, t_ctx *ctx)
{
    int pipes[2];
    int children;

    children = 0;
    if (pipe(pipes) == -1)
    {
        ft_fprintf(2, "pipe failed\n");
        exit(1);
    }
    if (fork() == 0)
    {
        dup2(pipes[1], STDOUT_FILENO);
        close(pipes[0]);
        close(pipes[1]);
        children += ft_exec_node(exec->data.pair.left, ctx);
    }
    if (fork() == 0)
    {
        dup2(pipes[0], STDIN_FILENO);
        close(pipes[0]);
        close(pipes[1]);
        children += ft_exec_node(exec->data.pair.right, ctx);
    }
    close(pipes[0]);
    close(pipes[1]);
    return (children);
}*/

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		;
	return(i);
}

static void	ft_adjust(t_ctx *ctx, char **tab, int i)
{
	int j;

	j = -1;
	ctx->fd_here_doc = malloc(sizeof(char *) * (i + 2));
	while(tab[++j])
	{
		ctx->fd_here_doc[j] = ft_strdup(tab[j]);
		free(tab[j]);
	}
	ctx->fd_here_doc[j] = 0;
	free(tab);
}

void	ft_is_here_doc(t_ctx *ctx, t_ast_node *tree)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = malloc(sizeof(char *) * 100);
	if (!tree)
		return ;
	while (tree->node_type == NODE_REDIR)
	{
		if (tree->data.redir.fd == 2)
			tmp[++i] = ft_strdup(tree->data.redir.file);
		tree = tree->data.redir.cmd;
	}
	tmp[++i] = 0;
	ctx->len = i;
	ctx->is_first = 0;
	ft_adjust(ctx, tmp, i);
}


void	ft_exec(t_ast_node *tree, t_ctx *ctx)
{
    t_fd    fds;
	int	    i;
	int	    children;
	
	if (!tree)
		exit(1);
	i = -1;
    fds.fd[0] = STDIN_FILENO;
	fds.fd[1] = STDOUT_FILENO;
	fds.fd_close = -1;
    fds.first_in = 1;
    fds.first_out = 1;	children = ft_exec_node(tree, ctx, &fds);
	while (++i < children)
		wait(0);
}

void    ft_get_heredoc(char *eof)
{
    char    *line;
    char    *limiter;
    int     fd;

    fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return ;
    line = "";
    limiter = eof;
    while (1)
    {
        ft_putstr_fd("> ", 1);
        line = get_next_line(STDIN_FILENO);
        if (line == NULL)
            break ;
        if (ft_strlen(limiter) + 1 == ft_strlen(line)
            && !ft_strncmp(line, limiter, ft_strlen(limiter)))
            break ;
        else
            ft_putstr_fd(line, fd);
        free(line);
    }
}

int	ft_exec_node(t_ast_node *node, t_ctx *ctx, t_fd *fds)
{
	int	ret;

	ret = 0;
	if (node->node_type == NODE_CMD)
	{
		ret = ft_exec_cmd(node, ctx, fds);
		unlink(".here_doc");
		return (ret);
	}
	else if (node->node_type == NODE_PIPE)
		return (ft_exec_pipe(node, ctx, fds));
	else if (node->node_type == NODE_REDIR)
	{
		ret = ft_exec_redir(node, ctx, fds);
		unlink(".here_doc");
        return (ret);
	}
	else
		return (0);
}

int    ft_exec_redir(t_ast_node *exec, t_ctx *ctx, t_fd *fds)
{
    int fd;

	if (ctx->is_first)
		ft_is_here_doc(ctx, exec);
	if (exec->data.redir.fd == 2)
	{
		ft_get_heredoc(ctx->fd_here_doc[--ctx->len]);
        fd = open(".here_doc", O_RDONLY);
	}
	else
    	fd = open(exec->data.redir.file, exec->data.redir.mode, 0664);
    if (fd == -1)
    {
        ft_fprintf(2, "open %s failed\n", exec->data.redir.file);
        exit(1);
    }
    if (fds->first_in && (exec->data.redir.fd == 0 || exec->data.redir.fd == 2))
    {
        fds->fd[0] = fd;
        fds->first_in = 0;
    }
    if (fds->first_out && exec->data.redir.fd == 1)
    {
        fds->fd[1] = fd;
        fds->first_out = 0;
    }	
    fds->fd_close = exec->data.redir.fd;
    if (!exec->data.redir.cmd || exec->data.redir.cmd->node_type == NODE_CMD)
    {
        fds->first_in = 1;       
        fds->first_out = 1;
		ctx->is_first = 1;
		ctx->len = 0;
    }
    ft_exec_node(exec->data.redir.cmd, ctx, fds);
    return (1);
}

/*int    ft_exec_end_or(t_ast_node *exec, t_ctx *ctx)
{
    pid_t   pid;
    int     status;
    int     children;

    children = 0;
    pid = fork();
    if (pid == 0)
        children += ft_exec_node(exec->data.pair.left, ctx);
    waitpid(pid, &status, 0);
    if (status == 2)
        status += 128;
    else
        status = WEXITSTATUS(status);
    if (exec->node_type == NODE_AND && status)
        children += ft_exec_node(exec->data.pair.left, ctx);
    return (children);
}*/

int	ft_exec_cmd(t_ast_node *node, t_ctx *ctx, t_fd *fds)
{
	char	*cmd_path;

	g_prompt.prompt = 0;
	if (fork() == CHILD_PROCESS)
	{
		if (fds->fd_close != fds->fd[STDIN_FILENO])
			dup2(fds->fd[STDIN_FILENO], STDIN_FILENO);
		if (fds->fd_close != fds->fd[STDOUT_FILENO])
			dup2(fds->fd[STDOUT_FILENO], STDOUT_FILENO);
		if (fds->fd[STDIN_FILENO] != STDIN_FILENO)
			close(fds->fd[STDIN_FILENO]);
		if (fds->fd[STDOUT_FILENO] != STDOUT_FILENO)
			close(fds->fd[STDOUT_FILENO]);
        if (node->data.cmd.tok_list[0] == 0)
            exit(1);
        cmd_path = ft_chr_path(node->data.cmd.tok_list[0], ctx->env);
        if (!cmd_path)
            ft_return_err(node->data.cmd.tok_list[0], "command not found");
        execve(cmd_path, node->data.cmd.tok_list, ctx->env);
        ft_fprintf(2, "exec %s failed\n", node->data.cmd.tok_list[0]);
	}
	return (1);
}

int	ft_exec_pipe(t_ast_node *node, t_ctx *ctx, t_fd *fds)
{
	int			p[2];
	int			children;
	t_ast_node	*left_exec;
	t_ast_node	*right_exec;
	t_fd		left_fds;
	t_fd		right_fds;

	pipe(p);
	children = 0;
	left_exec = node->data.pair.left;
	left_fds = *fds;
	left_fds.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
	left_fds.fd_close = p[STDIN_FILENO];
	children += ft_exec_node(left_exec, ctx,  &left_fds);
	close(p[STDOUT_FILENO]);
	unlink(".here_doc");
	right_exec = node->data.pair.right;
	right_fds = *fds;
	right_fds.fd[STDIN_FILENO] = p[STDIN_FILENO];
	right_fds.fd_close = p[STDOUT_FILENO];
	children += ft_exec_node(right_exec, ctx, &right_fds);
	close(p[STDIN_FILENO]);
	unlink(".here_doc");
	return (children);
}
