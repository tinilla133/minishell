/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fm_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmorenil <fmorenil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:27:28 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/03 18:07:18 by fmorenil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_new_pipe(int *fd, int last)
{
	if (close(fd[0]) == -1)
		ft_exit_error("Error close", 47);
	if (close(fd[1]) == -1)
		ft_exit_error("Error close", 48);
	if (last)
		pipe(fd);
}

void	ft_set_pipes(t_pipe *pipes, int i)
{
	if (!pipes->last)
	{
		ft_new_pipe(pipes->fd[0], pipes->last);
		ft_new_pipe(pipes->fd[1], pipes->last);
	}
	else if (i % 2)
		ft_new_pipe(pipes->fd[1], pipes->last);
	else
		ft_new_pipe(pipes->fd[0], pipes->last);
}

static void	ft_dup_pipe(int *io, int fd)
{
	if (close(*io) == -1)
		ft_exit_error("Close", 45);
	*io = dup(fd);
	if (*io == 1)
		ft_exit_error("Dup", 46);
}

void	ft_set_fds(t_pipe *pipe, int i)
{
	ft_dup_pipe(&(pipe->in), STDIN_FILENO);
	ft_dup_pipe(&(pipe->out), STDOUT_FILENO);
	if (i == 0)
		return ;
	else if (i % 2)
	{
		if (i != 1)
			ft_dup_pipe(&(pipe->in), pipe->fd[1][0]);
		if (pipe->last)
			ft_dup_pipe(&(pipe->out), pipe->fd[0][1]);
	}
	else
	{
		ft_dup_pipe(&(pipe->in), pipe->fd[0][0]);
		if (pipe->last)
			ft_dup_pipe(&(pipe->out), pipe->fd[1][1]);
	}
}

t_pipe	*ft_init_pipes(void)
{
	t_pipe	*pipes;

	pipes = ft_calloc(sizeof(t_pipe), 1);
	if (!pipes)
		ft_exit_error("Malloc", 40);
	if (pipe(pipes->fd[0]) == -1)
		ft_exit_error("Pipe", 41);
	if (pipe(pipes->fd[1]) == -1)
		ft_exit_error("Pipe", 42);
	pipes->in = dup(STDIN_FILENO);
	if (pipes->in == -1)
		ft_exit_error("Pipe", 43);
	pipes->out = dup(STDOUT_FILENO);
	if (pipes->out == -1)
		ft_exit_error("Pipe", 44);
	pipes->last = 1;
	pipes->out_error = STDERR_FILENO;
	return (pipes);
}
