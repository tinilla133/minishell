/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvizcaya <fvizcaya@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:27:52 by fmorenil          #+#    #+#             */
/*   Updated: 2024/12/13 19:35:57 by fvizcaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redir.h"

int	ft_heredoc(t_cmd *cmd, char *stop)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		ft_exit_error("Error pipe", 1);
	stop = ft_str_noquotes(stop);
	write(1, "heredoc> ", 9);
	line = get_next_line(cmd->pipes->in);
	while (line)
	{
		if (!ft_strncmp(line, stop, ft_strlen(stop)))
		{
			if ((ft_strlen(line) - 1) == ft_strlen(stop))
				break ;
		}
		write(1, "heredoc> ", 9);
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(cmd->pipes->in);
	}
	(free(line), free(stop));
	if (dup2(fd[0], cmd->pipes->in) == -1)
		return (perror("Error"), -1);
	(close(fd[0]), close(fd[1]));
	return (0);
}
